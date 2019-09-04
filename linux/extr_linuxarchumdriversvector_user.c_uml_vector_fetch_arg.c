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
struct arglist {int numargs; char** values; int /*<<< orphan*/ * tokens; } ;

/* Variables and functions */
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

char *uml_vector_fetch_arg(struct arglist *ifspec, char *token)
{
	int i;

	for (i = 0; i < ifspec->numargs; i++) {
		if (strcmp(ifspec->tokens[i], token) == 0)
			return ifspec->values[i];
	}
	return NULL;

}