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
struct gpmc_device {int nirqs; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  GPMC_IRQSTATUS ; 
 int GPMC_NR_NAND_IRQS ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  generic_handle_irq (int) ; 
 int /*<<< orphan*/  gpmc_irq_domain ; 
 int gpmc_read_reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpmc_write_reg (int /*<<< orphan*/ ,int) ; 
 int irq_find_mapping (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static irqreturn_t gpmc_handle_irq(int irq, void *data)
{
	int hwirq, virq;
	u32 regval, regvalx;
	struct gpmc_device *gpmc = data;

	regval = gpmc_read_reg(GPMC_IRQSTATUS);
	regvalx = regval;

	if (!regval)
		return IRQ_NONE;

	for (hwirq = 0; hwirq < gpmc->nirqs; hwirq++) {
		/* skip reserved status bits */
		if (hwirq == GPMC_NR_NAND_IRQS)
			regvalx >>= 8 - GPMC_NR_NAND_IRQS;

		if (regvalx & BIT(hwirq)) {
			virq = irq_find_mapping(gpmc_irq_domain, hwirq);
			if (!virq) {
				dev_warn(gpmc->dev,
					 "spurious irq detected hwirq %d, virq %d\n",
					 hwirq, virq);
			}

			generic_handle_irq(virq);
		}
	}

	gpmc_write_reg(GPMC_IRQSTATUS, regval);

	return IRQ_HANDLED;
}