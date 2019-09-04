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
typedef  int uint32_t ;
struct dcp {int /*<<< orphan*/ * completion; scalar_t__ base; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int DCP_MAX_CHANS ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 scalar_t__ MXS_DCP_STAT ; 
 scalar_t__ MXS_DCP_STAT_CLR ; 
 int MXS_DCP_STAT_IRQ_MASK ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static irqreturn_t mxs_dcp_irq(int irq, void *context)
{
	struct dcp *sdcp = context;
	uint32_t stat;
	int i;

	stat = readl(sdcp->base + MXS_DCP_STAT);
	stat &= MXS_DCP_STAT_IRQ_MASK;
	if (!stat)
		return IRQ_NONE;

	/* Clear the interrupts. */
	writel(stat, sdcp->base + MXS_DCP_STAT_CLR);

	/* Complete the DMA requests that finished. */
	for (i = 0; i < DCP_MAX_CHANS; i++)
		if (stat & (1 << i))
			complete(&sdcp->completion[i]);

	return IRQ_HANDLED;
}