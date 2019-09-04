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
 int HW_BREAKPOINT_LEN_8 ; 
 int HW_BREAKPOINT_R ; 
 int HW_BREAKPOINT_W ; 
#define  SH_BREAKPOINT_LEN_1 134 
#define  SH_BREAKPOINT_LEN_2 133 
#define  SH_BREAKPOINT_LEN_4 132 
#define  SH_BREAKPOINT_LEN_8 131 
#define  SH_BREAKPOINT_READ 130 
#define  SH_BREAKPOINT_RW 129 
#define  SH_BREAKPOINT_WRITE 128 

int arch_bp_generic_fields(int sh_len, int sh_type,
			   int *gen_len, int *gen_type)
{
	/* Len */
	switch (sh_len) {
	case SH_BREAKPOINT_LEN_1:
		*gen_len = HW_BREAKPOINT_LEN_1;
		break;
	case SH_BREAKPOINT_LEN_2:
		*gen_len = HW_BREAKPOINT_LEN_2;
		break;
	case SH_BREAKPOINT_LEN_4:
		*gen_len = HW_BREAKPOINT_LEN_4;
		break;
	case SH_BREAKPOINT_LEN_8:
		*gen_len = HW_BREAKPOINT_LEN_8;
		break;
	default:
		return -EINVAL;
	}

	/* Type */
	switch (sh_type) {
	case SH_BREAKPOINT_READ:
		*gen_type = HW_BREAKPOINT_R;
	case SH_BREAKPOINT_WRITE:
		*gen_type = HW_BREAKPOINT_W;
		break;
	case SH_BREAKPOINT_RW:
		*gen_type = HW_BREAKPOINT_W | HW_BREAKPOINT_R;
		break;
	default:
		return -EINVAL;
	}

	return 0;
}