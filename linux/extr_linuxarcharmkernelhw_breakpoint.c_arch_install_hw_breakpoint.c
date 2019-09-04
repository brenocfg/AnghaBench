#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct perf_event {int dummy; } ;
struct TYPE_2__ {scalar_t__ type; scalar_t__ enabled; } ;
struct arch_hw_breakpoint {int address; int trigger; TYPE_1__ ctrl; TYPE_1__ step_ctrl; } ;

/* Variables and functions */
 int ARM_BASE_BCR ; 
 int ARM_BASE_BVR ; 
 int ARM_BASE_WCR ; 
 int ARM_BASE_WVR ; 
 scalar_t__ ARM_BREAKPOINT_EXECUTE ; 
 int EBUSY ; 
 int /*<<< orphan*/  bp_on_reg ; 
 int core_num_brps ; 
 int core_num_wrps ; 
 struct arch_hw_breakpoint* counter_arch_bp (struct perf_event*) ; 
 int encode_ctrl_reg (TYPE_1__) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 struct perf_event** this_cpu_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wp_on_reg ; 
 int /*<<< orphan*/  write_wb_reg (int,int) ; 

int arch_install_hw_breakpoint(struct perf_event *bp)
{
	struct arch_hw_breakpoint *info = counter_arch_bp(bp);
	struct perf_event **slot, **slots;
	int i, max_slots, ctrl_base, val_base;
	u32 addr, ctrl;

	addr = info->address;
	ctrl = encode_ctrl_reg(info->ctrl) | 0x1;

	if (info->ctrl.type == ARM_BREAKPOINT_EXECUTE) {
		/* Breakpoint */
		ctrl_base = ARM_BASE_BCR;
		val_base = ARM_BASE_BVR;
		slots = this_cpu_ptr(bp_on_reg);
		max_slots = core_num_brps;
	} else {
		/* Watchpoint */
		ctrl_base = ARM_BASE_WCR;
		val_base = ARM_BASE_WVR;
		slots = this_cpu_ptr(wp_on_reg);
		max_slots = core_num_wrps;
	}

	for (i = 0; i < max_slots; ++i) {
		slot = &slots[i];

		if (!*slot) {
			*slot = bp;
			break;
		}
	}

	if (i == max_slots) {
		pr_warn("Can't find any breakpoint slot\n");
		return -EBUSY;
	}

	/* Override the breakpoint data with the step data. */
	if (info->step_ctrl.enabled) {
		addr = info->trigger & ~0x3;
		ctrl = encode_ctrl_reg(info->step_ctrl);
		if (info->ctrl.type != ARM_BREAKPOINT_EXECUTE) {
			i = 0;
			ctrl_base = ARM_BASE_BCR + core_num_brps;
			val_base = ARM_BASE_BVR + core_num_brps;
		}
	}

	/* Setup the address register. */
	write_wb_reg(val_base + i, addr);

	/* Setup the control register. */
	write_wb_reg(ctrl_base + i, ctrl);
	return 0;
}