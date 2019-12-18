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
struct mcde {int /*<<< orphan*/  dev; scalar_t__ regs; scalar_t__ te_sync; int /*<<< orphan*/  mdsi; } ;

/* Variables and functions */
 scalar_t__ MCDE_CHNL0SYNCHSW ; 
 int /*<<< orphan*/  MCDE_CHNLXSYNCHSW_SW_TRIG ; 
 int /*<<< orphan*/  MCDE_FIFO_A ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mcde_disable_fifo (struct mcde*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mcde_dsi_te_request (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcde_enable_fifo (struct mcde*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void mcde_display_send_one_frame(struct mcde *mcde)
{
	/* Request a TE ACK */
	if (mcde->te_sync)
		mcde_dsi_te_request(mcde->mdsi);

	/* Enable FIFO A flow */
	mcde_enable_fifo(mcde, MCDE_FIFO_A);

	if (mcde->te_sync) {
		/*
		 * If oneshot mode is enabled, the flow will be disabled
		 * when the TE0 IRQ arrives in the interrupt handler. Otherwise
		 * updates are continuously streamed to the display after this
		 * point.
		 */
		dev_dbg(mcde->dev, "sent TE0 framebuffer update\n");
		return;
	}

	/* Trigger a software sync out on channel 0 */
	writel(MCDE_CHNLXSYNCHSW_SW_TRIG,
	       mcde->regs + MCDE_CHNL0SYNCHSW);

	/*
	 * Disable FIFO A flow again: since we are using TE sync we
	 * need to wait for the FIFO to drain before we continue
	 * so repeated calls to this function will not cause a mess
	 * in the hardware by pushing updates will updates are going
	 * on already.
	 */
	mcde_disable_fifo(mcde, MCDE_FIFO_A, true);

	dev_dbg(mcde->dev, "sent SW framebuffer update\n");
}