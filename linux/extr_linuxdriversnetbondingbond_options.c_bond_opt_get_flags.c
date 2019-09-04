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
typedef  int u32 ;
struct bond_option {struct bond_opt_value const* values; } ;
struct bond_opt_value {int flags; scalar_t__ string; } ;

/* Variables and functions */

__attribute__((used)) static const struct bond_opt_value *bond_opt_get_flags(const struct bond_option *opt,
						       u32 flagmask)
{
	int i;

	for (i = 0; opt->values && opt->values[i].string; i++)
		if (opt->values[i].flags & flagmask)
			return &opt->values[i];

	return NULL;
}