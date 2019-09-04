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
struct irq_data {unsigned int hwirq; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (unsigned int) ; 
 int /*<<< orphan*/  GPMC_IRQSTATUS ; 
 unsigned int GPMC_NR_NAND_IRQS ; 
 int /*<<< orphan*/  gpmc_write_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gpmc_irq_ack(struct irq_data *d)
{
	unsigned int hwirq = d->hwirq;

	/* skip reserved bits */
	if (hwirq >= GPMC_NR_NAND_IRQS)
		hwirq += 8 - GPMC_NR_NAND_IRQS;

	/* Setting bit to 1 clears (or Acks) the interrupt */
	gpmc_write_reg(GPMC_IRQSTATUS, BIT(hwirq));
}