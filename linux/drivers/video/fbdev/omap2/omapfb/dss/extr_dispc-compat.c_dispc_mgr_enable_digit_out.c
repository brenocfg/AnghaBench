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
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_COMPLETION_ONSTACK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DSSERR (char*,...) ; 
 int /*<<< orphan*/  OMAP_DSS_CHANNEL_DIGIT ; 
 int /*<<< orphan*/  dispc_digit_out_enable_isr ; 
 int /*<<< orphan*/  dispc_mgr_enable (int /*<<< orphan*/ ,int) ; 
 int dispc_mgr_get_sync_lost_irq (int /*<<< orphan*/ ) ; 
 int dispc_mgr_get_vsync_irq (int /*<<< orphan*/ ) ; 
 scalar_t__ dispc_mgr_is_enabled (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int omap_dispc_register_isr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int omap_dispc_unregister_isr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vsync_compl ; 
 int /*<<< orphan*/  wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dispc_mgr_enable_digit_out(void)
{
	DECLARE_COMPLETION_ONSTACK(vsync_compl);
	int r;
	u32 irq_mask;

	if (dispc_mgr_is_enabled(OMAP_DSS_CHANNEL_DIGIT))
		return;

	/*
	 * Digit output produces some sync lost interrupts during the first
	 * frame when enabling. Those need to be ignored, so we register for the
	 * sync lost irq to prevent the error handler from triggering.
	 */

	irq_mask = dispc_mgr_get_vsync_irq(OMAP_DSS_CHANNEL_DIGIT) |
		dispc_mgr_get_sync_lost_irq(OMAP_DSS_CHANNEL_DIGIT);

	r = omap_dispc_register_isr(dispc_digit_out_enable_isr, &vsync_compl,
			irq_mask);
	if (r) {
		DSSERR("failed to register %x isr\n", irq_mask);
		return;
	}

	dispc_mgr_enable(OMAP_DSS_CHANNEL_DIGIT, true);

	/* wait for the first evsync */
	if (!wait_for_completion_timeout(&vsync_compl, msecs_to_jiffies(100)))
		DSSERR("timeout waiting for digit out to start\n");

	r = omap_dispc_unregister_isr(dispc_digit_out_enable_isr, &vsync_compl,
			irq_mask);
	if (r)
		DSSERR("failed to unregister %x isr\n", irq_mask);
}