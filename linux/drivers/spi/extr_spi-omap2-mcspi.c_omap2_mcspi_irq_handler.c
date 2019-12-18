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
struct omap2_mcspi {int /*<<< orphan*/  txdone; int /*<<< orphan*/  master; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  OMAP2_MCSPI_IRQENABLE ; 
 int /*<<< orphan*/  OMAP2_MCSPI_IRQSTATUS ; 
 int OMAP2_MCSPI_IRQSTATUS_EOW ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int mcspi_read_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcspi_write_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t omap2_mcspi_irq_handler(int irq, void *data)
{
	struct omap2_mcspi *mcspi = data;
	u32 irqstat;

	irqstat	= mcspi_read_reg(mcspi->master, OMAP2_MCSPI_IRQSTATUS);
	if (!irqstat)
		return IRQ_NONE;

	/* Disable IRQ and wakeup slave xfer task */
	mcspi_write_reg(mcspi->master, OMAP2_MCSPI_IRQENABLE, 0);
	if (irqstat & OMAP2_MCSPI_IRQSTATUS_EOW)
		complete(&mcspi->txdone);

	return IRQ_HANDLED;
}