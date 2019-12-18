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
struct irq_data {int irq; } ;
struct asic3 {int irq_base; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int ASIC3_INTMASK_MASK0 ; 
 scalar_t__ ASIC3_INTR_BASE ; 
 scalar_t__ ASIC3_INTR_INT_MASK ; 
 int ASIC3_NUM_GPIOS ; 
 int asic3_read_register (struct asic3*,scalar_t__) ; 
 int /*<<< orphan*/  asic3_write_register (struct asic3*,scalar_t__,int) ; 
 struct asic3* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void asic3_unmask_irq(struct irq_data *data)
{
	struct asic3 *asic = irq_data_get_irq_chip_data(data);
	int regval;
	unsigned long flags;

	raw_spin_lock_irqsave(&asic->lock, flags);
	regval = asic3_read_register(asic,
				     ASIC3_INTR_BASE +
				     ASIC3_INTR_INT_MASK);

	regval |= (ASIC3_INTMASK_MASK0 <<
		   (data->irq - (asic->irq_base + ASIC3_NUM_GPIOS)));

	asic3_write_register(asic,
			     ASIC3_INTR_BASE +
			     ASIC3_INTR_INT_MASK,
			     regval);
	raw_spin_unlock_irqrestore(&asic->lock, flags);
}