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
typedef  int uint8_t ;
struct lpc32xx_nand_host {int /*<<< orphan*/  comp_controller; int /*<<< orphan*/  comp_nand; int /*<<< orphan*/  io_base; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int MLCIRQ_CONTROLLER_READY ; 
 int MLCIRQ_NAND_READY ; 
 int /*<<< orphan*/  MLC_IRQ_SR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int readb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t lpc3xxx_nand_irq(int irq, struct lpc32xx_nand_host *host)
{
	uint8_t sr;

	/* Clear interrupt flag by reading status */
	sr = readb(MLC_IRQ_SR(host->io_base));
	if (sr & MLCIRQ_NAND_READY)
		complete(&host->comp_nand);
	if (sr & MLCIRQ_CONTROLLER_READY)
		complete(&host->comp_controller);

	return IRQ_HANDLED;
}