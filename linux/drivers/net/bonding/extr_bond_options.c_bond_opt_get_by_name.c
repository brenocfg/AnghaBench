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
struct bond_option {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int BOND_OPT_LAST ; 
 struct bond_option* bond_opt_get (int) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const*) ; 

const struct bond_option *bond_opt_get_by_name(const char *name)
{
	const struct bond_option *opt;
	int option;

	for (option = 0; option < BOND_OPT_LAST; option++) {
		opt = bond_opt_get(option);
		if (opt && !strcmp(opt->name, name))
			return opt;
	}

	return NULL;
}