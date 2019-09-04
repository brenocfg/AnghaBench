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
struct reg_field {int dummy; } ;

/* Variables and functions */
 scalar_t__ of_machine_is_compatible (char*) ; 
 struct reg_field const* sti_stih407_dvfs_regfields ; 

__attribute__((used)) static const struct reg_field *sti_cpufreq_match(void)
{
	if (of_machine_is_compatible("st,stih407") ||
	    of_machine_is_compatible("st,stih410"))
		return sti_stih407_dvfs_regfields;

	return NULL;
}