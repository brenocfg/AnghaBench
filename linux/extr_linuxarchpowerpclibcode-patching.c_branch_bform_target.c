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
 unsigned int const BRANCH_ABSOLUTE ; 

__attribute__((used)) static unsigned long branch_bform_target(const unsigned int *instr)
{
	signed long imm;

	imm = *instr & 0xFFFC;

	/* If the top bit of the immediate value is set this is negative */
	if (imm & 0x8000)
		imm -= 0x10000;

	if ((*instr & BRANCH_ABSOLUTE) == 0)
		imm += (unsigned long)instr;

	return (unsigned long)imm;
}