#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct fotg210_hcd {int command; TYPE_1__* regs; int /*<<< orphan*/  lock; } ;
struct TYPE_4__ {int /*<<< orphan*/  irq; } ;
struct TYPE_3__ {int /*<<< orphan*/  status; int /*<<< orphan*/  command; int /*<<< orphan*/  intr_enable; } ;

/* Variables and functions */
 int CMD_IAAD ; 
 int CMD_RUN ; 
 int /*<<< orphan*/  STS_HALT ; 
 int fotg210_readl (struct fotg210_hcd*,int /*<<< orphan*/ *) ; 
 TYPE_2__* fotg210_to_hcd (struct fotg210_hcd*) ; 
 int /*<<< orphan*/  fotg210_writel (struct fotg210_hcd*,int,int /*<<< orphan*/ *) ; 
 int handshake (struct fotg210_hcd*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  synchronize_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fotg210_halt(struct fotg210_hcd *fotg210)
{
	u32 temp;

	spin_lock_irq(&fotg210->lock);

	/* disable any irqs left enabled by previous code */
	fotg210_writel(fotg210, 0, &fotg210->regs->intr_enable);

	/*
	 * This routine gets called during probe before fotg210->command
	 * has been initialized, so we can't rely on its value.
	 */
	fotg210->command &= ~CMD_RUN;
	temp = fotg210_readl(fotg210, &fotg210->regs->command);
	temp &= ~(CMD_RUN | CMD_IAAD);
	fotg210_writel(fotg210, temp, &fotg210->regs->command);

	spin_unlock_irq(&fotg210->lock);
	synchronize_irq(fotg210_to_hcd(fotg210)->irq);

	return handshake(fotg210, &fotg210->regs->status,
			STS_HALT, STS_HALT, 16 * 125);
}