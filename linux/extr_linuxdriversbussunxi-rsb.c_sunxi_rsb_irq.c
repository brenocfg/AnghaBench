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
struct sunxi_rsb {int status; int /*<<< orphan*/  complete; scalar_t__ regs; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ RSB_INTS ; 
 int RSB_INTS_LOAD_BSY ; 
 int RSB_INTS_TRANS_ERR ; 
 int RSB_INTS_TRANS_OVER ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static irqreturn_t sunxi_rsb_irq(int irq, void *dev_id)
{
	struct sunxi_rsb *rsb = dev_id;
	u32 status;

	status = readl(rsb->regs + RSB_INTS);
	rsb->status = status;

	/* Clear interrupts */
	status &= (RSB_INTS_LOAD_BSY | RSB_INTS_TRANS_ERR |
		   RSB_INTS_TRANS_OVER);
	writel(status, rsb->regs + RSB_INTS);

	complete(&rsb->complete);

	return IRQ_HANDLED;
}