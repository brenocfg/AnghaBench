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

/* Variables and functions */
 unsigned long branch_bform_target (unsigned int const*) ; 
 unsigned long branch_iform_target (unsigned int const*) ; 
 scalar_t__ instr_is_branch_bform (unsigned int const) ; 
 scalar_t__ instr_is_branch_iform (unsigned int const) ; 

unsigned long branch_target(const unsigned int *instr)
{
	if (instr_is_branch_iform(*instr))
		return branch_iform_target(instr);
	else if (instr_is_branch_bform(*instr))
		return branch_bform_target(instr);

	return 0;
}