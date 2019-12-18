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
struct pic32_sqi {scalar_t__ regs; int /*<<< orphan*/  xfer_done; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int PESQI_BDDONE ; 
 int PESQI_DMAERR ; 
 scalar_t__ PESQI_INT_ENABLE_REG ; 
 scalar_t__ PESQI_INT_STAT_REG ; 
 int PESQI_PKTCOMP ; 
 int PESQI_RXEMPTY ; 
 int PESQI_RXFULL ; 
 int PESQI_RXTHR ; 
 int PESQI_TXEMPTY ; 
 int PESQI_TXFULL ; 
 int PESQI_TXTHR ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static irqreturn_t pic32_sqi_isr(int irq, void *dev_id)
{
	struct pic32_sqi *sqi = dev_id;
	u32 enable, status;

	enable = readl(sqi->regs + PESQI_INT_ENABLE_REG);
	status = readl(sqi->regs + PESQI_INT_STAT_REG);

	/* check spurious interrupt */
	if (!status)
		return IRQ_NONE;

	if (status & PESQI_DMAERR) {
		enable = 0;
		goto irq_done;
	}

	if (status & PESQI_TXTHR)
		enable &= ~(PESQI_TXTHR | PESQI_TXFULL | PESQI_TXEMPTY);

	if (status & PESQI_RXTHR)
		enable &= ~(PESQI_RXTHR | PESQI_RXFULL | PESQI_RXEMPTY);

	if (status & PESQI_BDDONE)
		enable &= ~PESQI_BDDONE;

	/* packet processing completed */
	if (status & PESQI_PKTCOMP) {
		/* mask all interrupts */
		enable = 0;
		/* complete trasaction */
		complete(&sqi->xfer_done);
	}

irq_done:
	/* interrupts are sticky, so mask when handled */
	writel(enable, sqi->regs + PESQI_INT_ENABLE_REG);

	return IRQ_HANDLED;
}