open ReasonLambda.V2;

type greetings = {greetings: string};

let defaultName = "Anon";

let handler: handler =
  (
    {
      pathParameters,
      queryStringParameters,
      requestContext: {http: {userAgent}},
    },
    {functionName},
  ) => {
    let title =
      switch (queryStringParameters) {
      | Some(queryStringParameters) =>
        queryStringParameters
        ->Js.Dict.get("title")
        ->Belt.Option.getWithDefault("")
      | None => ""
      };
    let title = title === "" ? "" : title ++ " ";
    let name =
      switch (pathParameters) {
      | Some(pathParameters) =>
        pathParameters
        ->Js.Dict.get("name")
        ->Belt.Option.getWithDefault(defaultName)
      | None => defaultName
      };
    let greetings = {j|Hello $title$name, you're making this request to $functionName from $userAgent|j};
    {greetings: greetings}->Response.fromBody->Js.Promise.resolve;
  };