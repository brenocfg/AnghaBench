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
 int /*<<< orphan*/  hv_synic_disable_regs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hv_synic_suspend(void)
{
	/*
	 * When we reach here, all the non-boot CPUs have been offlined, and
	 * the stimers on them have been unbound in hv_synic_cleanup() ->
	 * hv_stimer_cleanup() -> clockevents_unbind_device().
	 *
	 * hv_synic_suspend() only runs on CPU0 with interrupts disabled. Here
	 * we do not unbind the stimer on CPU0 because: 1) it's unnecessary
	 * because the interrupts remain disabled between syscore_suspend()
	 * and syscore_resume(): see create_image() and resume_target_kernel();
	 * 2) the stimer on CPU0 is automatically disabled later by
	 * syscore_suspend() -> timekeeping_suspend() -> tick_suspend() -> ...
	 * -> clockevents_shutdown() -> ... -> hv_ce_shutdown(); 3) a warning
	 * would be triggered if we call clockevents_unbind_device(), which
	 * may sleep, in an interrupts-disabled context. So, we intentionally
	 * don't call hv_stimer_cleanup(0) here.
	 */

	hv_synic_disable_regs(0);

	return 0;
}