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
typedef  scalar_t__ u32 ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_COMPLETION_ONSTACK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DSSERR (char*,...) ; 
 int /*<<< orphan*/  OMAP_DSS_CHANNEL_DIGIT ; 
 int /*<<< orphan*/  dispc_mgr_disable_isr ; 
 int /*<<< orphan*/  dispc_mgr_enable (int /*<<< orphan*/ ,int) ; 
 scalar_t__ dispc_mgr_get_framedone_irq (int /*<<< orphan*/ ) ; 
 scalar_t__ dispc_mgr_get_vsync_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dispc_mgr_is_enabled (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  framedone_compl ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int omap_dispc_register_isr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int omap_dispc_unregister_isr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dispc_mgr_disable_digit_out(void)
{
	DECLARE_COMPLETION_ONSTACK(framedone_compl);
	int r, i;
	u32 irq_mask;
	int num_irqs;

	if (!dispc_mgr_is_enabled(OMAP_DSS_CHANNEL_DIGIT))
		return;

	/*
	 * When we disable the digit output, we need to wait for FRAMEDONE to
	 * know that DISPC has finished with the output.
	 */

	irq_mask = dispc_mgr_get_framedone_irq(OMAP_DSS_CHANNEL_DIGIT);
	num_irqs = 1;

	if (!irq_mask) {
		/*
		 * omap 2/3 don't have framedone irq for TV, so we need to use
		 * vsyncs for this.
		 */

		irq_mask = dispc_mgr_get_vsync_irq(OMAP_DSS_CHANNEL_DIGIT);
		/*
		 * We need to wait for both even and odd vsyncs. Note that this
		 * is not totally reliable, as we could get a vsync interrupt
		 * before we disable the output, which leads to timeout in the
		 * wait_for_completion.
		 */
		num_irqs = 2;
	}

	r = omap_dispc_register_isr(dispc_mgr_disable_isr, &framedone_compl,
			irq_mask);
	if (r)
		DSSERR("failed to register %x isr\n", irq_mask);

	dispc_mgr_enable(OMAP_DSS_CHANNEL_DIGIT, false);

	/* if we couldn't register the irq, just sleep and exit */
	if (r) {
		msleep(100);
		return;
	}

	for (i = 0; i < num_irqs; ++i) {
		if (!wait_for_completion_timeout(&framedone_compl,
					msecs_to_jiffies(100)))
			DSSERR("timeout waiting for digit out to stop\n");
	}

	r = omap_dispc_unregister_isr(dispc_mgr_disable_isr, &framedone_compl,
			irq_mask);
	if (r)
		DSSERR("failed to unregister %x isr\n", irq_mask);
}