#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_6__ {int dma_conf; scalar_t__ regs; int /*<<< orphan*/  d_next; scalar_t__ desc_mode; } ;
struct ast_vhub_ep {TYPE_3__ epn; TYPE_2__* vhub; } ;
struct TYPE_5__ {TYPE_1__* pdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ AST_VHUB_EP_DESC_STATUS ; 
 scalar_t__ AST_VHUB_EP_DMA_CTLSTAT ; 
 int EP_DMA_PROC_RX_IDLE ; 
 int EP_DMA_PROC_TX_IDLE ; 
 int VHUB_EP_DMA_PROC_STATUS (int) ; 
 int VHUB_EP_DMA_SET_CPU_WPTR (int /*<<< orphan*/ ) ; 
 int VHUB_EP_DMA_SET_RPTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void ast_vhub_stop_active_req(struct ast_vhub_ep *ep,
				     bool restart_ep)
{
	u32 state, reg, loops;

	/* Stop DMA activity */
	writel(0, ep->epn.regs + AST_VHUB_EP_DMA_CTLSTAT);

	/* Wait for it to complete */
	for (loops = 0; loops < 1000; loops++) {
		state = readl(ep->epn.regs + AST_VHUB_EP_DMA_CTLSTAT);
		state = VHUB_EP_DMA_PROC_STATUS(state);
		if (state == EP_DMA_PROC_RX_IDLE ||
		    state == EP_DMA_PROC_TX_IDLE)
			break;
		udelay(1);
	}
	if (loops >= 1000)
		dev_warn(&ep->vhub->pdev->dev, "Timeout waiting for DMA\n");

	/* If we don't have to restart the endpoint, that's it */
	if (!restart_ep)
		return;

	/* Restart the endpoint */
	if (ep->epn.desc_mode) {
		/*
		 * Take out descriptors by resetting the DMA read
		 * pointer to be equal to the CPU write pointer.
		 *
		 * Note: If we ever support creating descriptors for
		 * requests that aren't the head of the queue, we
		 * may have to do something more complex here,
		 * especially if the request being taken out is
		 * not the current head descriptors.
		 */
		reg = VHUB_EP_DMA_SET_RPTR(ep->epn.d_next) |
			VHUB_EP_DMA_SET_CPU_WPTR(ep->epn.d_next);
		writel(reg, ep->epn.regs + AST_VHUB_EP_DESC_STATUS);

		/* Then turn it back on */
		writel(ep->epn.dma_conf,
		       ep->epn.regs + AST_VHUB_EP_DMA_CTLSTAT);
	} else {
		/* Single mode: just turn it back on */
		writel(ep->epn.dma_conf,
		       ep->epn.regs + AST_VHUB_EP_DMA_CTLSTAT);
	}
}