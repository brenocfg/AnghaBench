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
struct sun4i_ps2data {int /*<<< orphan*/  lock; scalar_t__ reg_base; int /*<<< orphan*/  serio; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int PS2_FIFO_ERROR_BIT ; 
 int PS2_FSTS_RXOF ; 
 int PS2_FSTS_RXRDY ; 
 int PS2_FSTS_RXUF ; 
 int PS2_FSTS_TXOF ; 
 int PS2_FSTS_TXRDY ; 
 int PS2_FSTS_TXUF ; 
 int PS2_LINE_ERROR_BIT ; 
 int PS2_LSTS_ACKERR ; 
 int PS2_LSTS_PARERR ; 
 int PS2_LSTS_RXTDO ; 
 int PS2_LSTS_STOPERR ; 
 int PS2_LSTS_TXTDO ; 
 scalar_t__ PS2_REG_DATA ; 
 scalar_t__ PS2_REG_FSTS ; 
 scalar_t__ PS2_REG_LSTS ; 
 unsigned int SERIO_FRAME ; 
 unsigned int SERIO_PARITY ; 
 unsigned int SERIO_TIMEOUT ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  serio_interrupt (int /*<<< orphan*/ ,unsigned char,unsigned int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static irqreturn_t sun4i_ps2_interrupt(int irq, void *dev_id)
{
	struct sun4i_ps2data *drvdata = dev_id;
	u32 intr_status;
	u32 fifo_status;
	unsigned char byte;
	unsigned int rxflags = 0;
	u32 rval;

	spin_lock(&drvdata->lock);

	/* Get the PS/2 interrupts and clear them */
	intr_status  = readl(drvdata->reg_base + PS2_REG_LSTS);
	fifo_status  = readl(drvdata->reg_base + PS2_REG_FSTS);

	/* Check line status register */
	if (intr_status & PS2_LINE_ERROR_BIT) {
		rxflags = (intr_status & PS2_LINE_ERROR_BIT) ? SERIO_FRAME : 0;
		rxflags |= (intr_status & PS2_LSTS_PARERR) ? SERIO_PARITY : 0;
		rxflags |= (intr_status & PS2_LSTS_PARERR) ? SERIO_TIMEOUT : 0;

		rval = PS2_LSTS_TXTDO | PS2_LSTS_STOPERR | PS2_LSTS_ACKERR |
			PS2_LSTS_PARERR | PS2_LSTS_RXTDO;
		writel(rval, drvdata->reg_base + PS2_REG_LSTS);
	}

	/* Check FIFO status register */
	if (fifo_status & PS2_FIFO_ERROR_BIT) {
		rval = PS2_FSTS_TXUF | PS2_FSTS_TXOF | PS2_FSTS_TXRDY |
			PS2_FSTS_RXUF | PS2_FSTS_RXOF | PS2_FSTS_RXRDY;
		writel(rval, drvdata->reg_base + PS2_REG_FSTS);
	}

	rval = (fifo_status >> 16) & 0x3;
	while (rval--) {
		byte = readl(drvdata->reg_base + PS2_REG_DATA) & 0xff;
		serio_interrupt(drvdata->serio, byte, rxflags);
	}

	writel(intr_status, drvdata->reg_base + PS2_REG_LSTS);
	writel(fifo_status, drvdata->reg_base + PS2_REG_FSTS);

	spin_unlock(&drvdata->lock);

	return IRQ_HANDLED;
}