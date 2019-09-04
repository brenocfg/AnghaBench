#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
typedef  void* u32 ;
struct pt_regs {int dummy; } ;
struct perf_event {int dummy; } ;
struct debug_info {int wps_disabled; int suspended_step; scalar_t__ bps_disabled; } ;
struct arch_hw_breakpoint_ctrl {int dummy; } ;
struct arch_hw_breakpoint {unsigned long trigger; } ;
struct TYPE_4__ {struct debug_info debug; } ;
struct TYPE_5__ {TYPE_1__ thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  AARCH64_DBG_REG_WCR ; 
 int /*<<< orphan*/  AARCH64_DBG_REG_WVR ; 
 unsigned int AARCH64_ESR_ACCESS_MASK ; 
 int ARM_KERNEL_STEP_ACTIVE ; 
 int ARM_KERNEL_STEP_NONE ; 
 int ARM_KERNEL_STEP_SUSPEND ; 
 int /*<<< orphan*/  DBG_ACTIVE_EL0 ; 
 int /*<<< orphan*/  DBG_ACTIVE_EL1 ; 
 int HW_BREAKPOINT_R ; 
 int HW_BREAKPOINT_W ; 
 int /*<<< orphan*/  TIF_SINGLESTEP ; 
 int core_num_wrps ; 
 struct arch_hw_breakpoint* counter_arch_bp (struct perf_event*) ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  decode_ctrl_reg (void*,struct arch_hw_breakpoint_ctrl*) ; 
 scalar_t__ get_distance_from_watchpoint (unsigned long,scalar_t__,struct arch_hw_breakpoint_ctrl*) ; 
 int hw_breakpoint_type (struct perf_event*) ; 
 scalar_t__ is_default_overflow_handler (struct perf_event*) ; 
 scalar_t__ kernel_active_single_step () ; 
 int /*<<< orphan*/  kernel_enable_single_step (struct pt_regs*) ; 
 int /*<<< orphan*/  perf_bp_event (struct perf_event*,struct pt_regs*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 void* read_wb_reg (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stepping_kernel_bp ; 
 scalar_t__ test_thread_flag (int /*<<< orphan*/ ) ; 
 void* this_cpu_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  toggle_bp_registers (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  user_enable_single_step (TYPE_2__*) ; 
 scalar_t__ user_mode (struct pt_regs*) ; 
 int /*<<< orphan*/ * wp_on_reg ; 

__attribute__((used)) static int watchpoint_handler(unsigned long addr, unsigned int esr,
			      struct pt_regs *regs)
{
	int i, step = 0, *kernel_step, access, closest_match = 0;
	u64 min_dist = -1, dist;
	u32 ctrl_reg;
	u64 val;
	struct perf_event *wp, **slots;
	struct debug_info *debug_info;
	struct arch_hw_breakpoint *info;
	struct arch_hw_breakpoint_ctrl ctrl;

	slots = this_cpu_ptr(wp_on_reg);
	debug_info = &current->thread.debug;

	/*
	 * Find all watchpoints that match the reported address. If no exact
	 * match is found. Attribute the hit to the closest watchpoint.
	 */
	rcu_read_lock();
	for (i = 0; i < core_num_wrps; ++i) {
		wp = slots[i];
		if (wp == NULL)
			continue;

		/*
		 * Check that the access type matches.
		 * 0 => load, otherwise => store
		 */
		access = (esr & AARCH64_ESR_ACCESS_MASK) ? HW_BREAKPOINT_W :
			 HW_BREAKPOINT_R;
		if (!(access & hw_breakpoint_type(wp)))
			continue;

		/* Check if the watchpoint value and byte select match. */
		val = read_wb_reg(AARCH64_DBG_REG_WVR, i);
		ctrl_reg = read_wb_reg(AARCH64_DBG_REG_WCR, i);
		decode_ctrl_reg(ctrl_reg, &ctrl);
		dist = get_distance_from_watchpoint(addr, val, &ctrl);
		if (dist < min_dist) {
			min_dist = dist;
			closest_match = i;
		}
		/* Is this an exact match? */
		if (dist != 0)
			continue;

		info = counter_arch_bp(wp);
		info->trigger = addr;
		perf_bp_event(wp, regs);

		/* Do we need to handle the stepping? */
		if (is_default_overflow_handler(wp))
			step = 1;
	}
	if (min_dist > 0 && min_dist != -1) {
		/* No exact match found. */
		wp = slots[closest_match];
		info = counter_arch_bp(wp);
		info->trigger = addr;
		perf_bp_event(wp, regs);

		/* Do we need to handle the stepping? */
		if (is_default_overflow_handler(wp))
			step = 1;
	}
	rcu_read_unlock();

	if (!step)
		return 0;

	/*
	 * We always disable EL0 watchpoints because the kernel can
	 * cause these to fire via an unprivileged access.
	 */
	toggle_bp_registers(AARCH64_DBG_REG_WCR, DBG_ACTIVE_EL0, 0);

	if (user_mode(regs)) {
		debug_info->wps_disabled = 1;

		/* If we're already stepping a breakpoint, just return. */
		if (debug_info->bps_disabled)
			return 0;

		if (test_thread_flag(TIF_SINGLESTEP))
			debug_info->suspended_step = 1;
		else
			user_enable_single_step(current);
	} else {
		toggle_bp_registers(AARCH64_DBG_REG_WCR, DBG_ACTIVE_EL1, 0);
		kernel_step = this_cpu_ptr(&stepping_kernel_bp);

		if (*kernel_step != ARM_KERNEL_STEP_NONE)
			return 0;

		if (kernel_active_single_step()) {
			*kernel_step = ARM_KERNEL_STEP_SUSPEND;
		} else {
			*kernel_step = ARM_KERNEL_STEP_ACTIVE;
			kernel_enable_single_step(regs);
		}
	}

	return 0;
}