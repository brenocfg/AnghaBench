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
struct p2wi {unsigned long status; int /*<<< orphan*/  complete; scalar_t__ regs; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ P2WI_INTS ; 
 unsigned long P2WI_INTS_LOAD_BSY ; 
 unsigned long P2WI_INTS_TRANS_ERR ; 
 unsigned long P2WI_INTS_TRANS_OVER ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 unsigned long readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (unsigned long,scalar_t__) ; 

__attribute__((used)) static irqreturn_t p2wi_interrupt(int irq, void *dev_id)
{
	struct p2wi *p2wi = dev_id;
	unsigned long status;

	status = readl(p2wi->regs + P2WI_INTS);
	p2wi->status = status;

	/* Clear interrupts */
	status &= (P2WI_INTS_LOAD_BSY | P2WI_INTS_TRANS_ERR |
		   P2WI_INTS_TRANS_OVER);
	writel(status, p2wi->regs + P2WI_INTS);

	complete(&p2wi->complete);

	return IRQ_HANDLED;
}