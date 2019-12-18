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
struct armada_37xx_pmx_func {int ngroups; char const* name; } ;

/* Variables and functions */
 int EEXIST ; 
 int EOVERFLOW ; 
 scalar_t__ strcmp (char const*,char const*) ; 

__attribute__((used)) static int armada_37xx_add_function(struct armada_37xx_pmx_func *funcs,
				    int *funcsize, const char *name)
{
	int i = 0;

	if (*funcsize <= 0)
		return -EOVERFLOW;

	while (funcs->ngroups) {
		/* function already there */
		if (strcmp(funcs->name, name) == 0) {
			funcs->ngroups++;

			return -EEXIST;
		}
		funcs++;
		i++;
	}

	/* append new unique function */
	funcs->name = name;
	funcs->ngroups = 1;
	(*funcsize)--;

	return 0;
}