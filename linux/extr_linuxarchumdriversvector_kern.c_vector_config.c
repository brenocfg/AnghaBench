#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct arglist {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 char* kstrdup (char*,int /*<<< orphan*/ ) ; 
 struct arglist* uml_parse_vector_ifspec (char*) ; 
 int /*<<< orphan*/  vector_eth_configure (int,struct arglist*) ; 
 int vector_parse (char*,int*,char**,char**) ; 

__attribute__((used)) static int vector_config(char *str, char **error_out)
{
	int err, n;
	char *params;
	struct arglist *parsed;

	err = vector_parse(str, &n, &params, error_out);
	if (err != 0)
		return err;

	/* This string is broken up and the pieces used by the underlying
	 * driver. We should copy it to make sure things do not go wrong
	 * later.
	 */

	params = kstrdup(params, GFP_KERNEL);
	if (params == NULL) {
		*error_out = "vector_config failed to strdup string";
		return -ENOMEM;
	}

	parsed = uml_parse_vector_ifspec(params);

	if (parsed == NULL) {
		*error_out = "vector_config failed to parse parameters";
		return -EINVAL;
	}

	vector_eth_configure(n, parsed);
	return 0;
}