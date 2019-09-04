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
struct perf_event_attr {int dummy; } ;
struct perf_event {int dummy; } ;
struct arch_hw_breakpoint {int len; unsigned int address; } ;

/* Variables and functions */
 int EINVAL ; 
#define  SH_BREAKPOINT_LEN_1 131 
#define  SH_BREAKPOINT_LEN_2 130 
#define  SH_BREAKPOINT_LEN_4 129 
#define  SH_BREAKPOINT_LEN_8 128 
 int arch_build_bp_info (struct perf_event*,struct perf_event_attr const*,struct arch_hw_breakpoint*) ; 

int hw_breakpoint_arch_parse(struct perf_event *bp,
			     const struct perf_event_attr *attr,
			     struct arch_hw_breakpoint *hw)
{
	unsigned int align;
	int ret;

	ret = arch_build_bp_info(bp, attr, hw);
	if (ret)
		return ret;

	ret = -EINVAL;

	switch (hw->len) {
	case SH_BREAKPOINT_LEN_1:
		align = 0;
		break;
	case SH_BREAKPOINT_LEN_2:
		align = 1;
		break;
	case SH_BREAKPOINT_LEN_4:
		align = 3;
		break;
	case SH_BREAKPOINT_LEN_8:
		align = 7;
		break;
	default:
		return ret;
	}

	/*
	 * Check that the low-order bits of the address are appropriate
	 * for the alignment implied by len.
	 */
	if (hw->address & align)
		return -EINVAL;

	return 0;
}