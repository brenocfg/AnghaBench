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
 int EINVAL ; 
 int HW_BREAKPOINT_LEN_1 ; 
 int HW_BREAKPOINT_LEN_2 ; 
 int HW_BREAKPOINT_LEN_4 ; 
#define  X86_BREAKPOINT_LEN_1 130 
#define  X86_BREAKPOINT_LEN_2 129 
#define  X86_BREAKPOINT_LEN_4 128 

__attribute__((used)) static int arch_bp_generic_len(int x86_len)
{
	switch (x86_len) {
	case X86_BREAKPOINT_LEN_1:
		return HW_BREAKPOINT_LEN_1;
	case X86_BREAKPOINT_LEN_2:
		return HW_BREAKPOINT_LEN_2;
	case X86_BREAKPOINT_LEN_4:
		return HW_BREAKPOINT_LEN_4;
#ifdef CONFIG_X86_64
	case X86_BREAKPOINT_LEN_8:
		return HW_BREAKPOINT_LEN_8;
#endif
	default:
		return -EINVAL;
	}
}