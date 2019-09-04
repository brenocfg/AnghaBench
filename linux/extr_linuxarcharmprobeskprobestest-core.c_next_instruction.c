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

__attribute__((used)) static unsigned long next_instruction(unsigned long pc)
{
#ifdef CONFIG_THUMB2_KERNEL
	if ((pc & 1) &&
	    !is_wide_instruction(__mem_to_opcode_thumb16(*(u16 *)(pc - 1))))
		return pc + 2;
	else
#endif
	return pc + 4;
}