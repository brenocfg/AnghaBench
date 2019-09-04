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
 scalar_t__ ARM_DEBUG_ARCH_V7_1 ; 
 scalar_t__ get_debug_arch () ; 
 int get_num_wrp_resources () ; 

__attribute__((used)) static int get_num_wrps(void)
{
	/*
	 * On debug architectures prior to 7.1, when a watchpoint fires, the
	 * only way to work out which watchpoint it was is by disassembling
	 * the faulting instruction and working out the address of the memory
	 * access.
	 *
	 * Furthermore, we can only do this if the watchpoint was precise
	 * since imprecise watchpoints prevent us from calculating register
	 * based addresses.
	 *
	 * Providing we have more than 1 breakpoint register, we only report
	 * a single watchpoint register for the time being. This way, we always
	 * know which watchpoint fired. In the future we can either add a
	 * disassembler and address generation emulator, or we can insert a
	 * check to see if the DFAR is set on watchpoint exception entry
	 * [the ARM ARM states that the DFAR is UNKNOWN, but experience shows
	 * that it is set on some implementations].
	 */
	if (get_debug_arch() < ARM_DEBUG_ARCH_V7_1)
		return 1;

	return get_num_wrp_resources();
}