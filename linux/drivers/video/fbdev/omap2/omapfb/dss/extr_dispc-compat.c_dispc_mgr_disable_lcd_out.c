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
typedef  int /*<<< orphan*/  u32 ;
typedef  enum omap_channel { ____Placeholder_omap_channel } omap_channel ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_COMPLETION_ONSTACK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DSSERR (char*) ; 
 int /*<<< orphan*/  dispc_mgr_disable_isr ; 
 int /*<<< orphan*/  dispc_mgr_enable (int,int) ; 
 int /*<<< orphan*/  dispc_mgr_get_framedone_irq (int) ; 
 int /*<<< orphan*/  dispc_mgr_is_enabled (int) ; 
 int /*<<< orphan*/  framedone_compl ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int omap_dispc_register_isr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int omap_dispc_unregister_isr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dispc_mgr_disable_lcd_out(enum omap_channel channel)
{
	DECLARE_COMPLETION_ONSTACK(framedone_compl);
	int r;
	u32 irq;

	if (!dispc_mgr_is_enabled(channel))
		return;

	/*
	 * When we disable LCD output, we need to wait for FRAMEDONE to know
	 * that DISPC has finished with the LCD output.
	 */

	irq = dispc_mgr_get_framedone_irq(channel);

	r = omap_dispc_register_isr(dispc_mgr_disable_isr, &framedone_compl,
			irq);
	if (r)
		DSSERR("failed to register FRAMEDONE isr\n");

	dispc_mgr_enable(channel, false);

	/* if we couldn't register for framedone, just sleep and exit */
	if (r) {
		msleep(100);
		return;
	}

	if (!wait_for_completion_timeout(&framedone_compl,
				msecs_to_jiffies(100)))
		DSSERR("timeout waiting for FRAME DONE\n");

	r = omap_dispc_unregister_isr(dispc_mgr_disable_isr, &framedone_compl,
			irq);
	if (r)
		DSSERR("failed to unregister FRAMEDONE isr\n");
}