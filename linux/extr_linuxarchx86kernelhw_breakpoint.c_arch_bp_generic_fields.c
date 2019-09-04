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
 int HW_BREAKPOINT_R ; 
 int HW_BREAKPOINT_W ; 
 int HW_BREAKPOINT_X ; 
#define  X86_BREAKPOINT_EXECUTE 130 
 int X86_BREAKPOINT_LEN_X ; 
#define  X86_BREAKPOINT_RW 129 
#define  X86_BREAKPOINT_WRITE 128 
 int arch_bp_generic_len (int) ; 

int arch_bp_generic_fields(int x86_len, int x86_type,
			   int *gen_len, int *gen_type)
{
	int len;

	/* Type */
	switch (x86_type) {
	case X86_BREAKPOINT_EXECUTE:
		if (x86_len != X86_BREAKPOINT_LEN_X)
			return -EINVAL;

		*gen_type = HW_BREAKPOINT_X;
		*gen_len = sizeof(long);
		return 0;
	case X86_BREAKPOINT_WRITE:
		*gen_type = HW_BREAKPOINT_W;
		break;
	case X86_BREAKPOINT_RW:
		*gen_type = HW_BREAKPOINT_W | HW_BREAKPOINT_R;
		break;
	default:
		return -EINVAL;
	}

	/* Len */
	len = arch_bp_generic_len(x86_len);
	if (len < 0)
		return -EINVAL;
	*gen_len = len;

	return 0;
}