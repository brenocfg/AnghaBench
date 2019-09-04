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
 unsigned int BRANCH_ABSOLUTE ; 
 scalar_t__ instr_is_branch_bform (unsigned int) ; 
 scalar_t__ instr_is_branch_iform (unsigned int) ; 

int instr_is_relative_branch(unsigned int instr)
{
	if (instr & BRANCH_ABSOLUTE)
		return 0;

	return instr_is_branch_iform(instr) || instr_is_branch_bform(instr);
}