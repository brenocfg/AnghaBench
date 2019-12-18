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
struct irq_data {int /*<<< orphan*/  irq; } ;
struct asic3 {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int ASIC3_GPIO_MASK ; 
 int asic3_irq_to_bank (struct asic3*,int /*<<< orphan*/ ) ; 
 int asic3_irq_to_index (struct asic3*,int /*<<< orphan*/ ) ; 
 int asic3_read_register (struct asic3*,int) ; 
 int /*<<< orphan*/  asic3_write_register (struct asic3*,int,int) ; 
 struct asic3* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void asic3_unmask_gpio_irq(struct irq_data *data)
{
	struct asic3 *asic = irq_data_get_irq_chip_data(data);
	u32 val, bank, index;
	unsigned long flags;

	bank = asic3_irq_to_bank(asic, data->irq);
	index = asic3_irq_to_index(asic, data->irq);

	raw_spin_lock_irqsave(&asic->lock, flags);
	val = asic3_read_register(asic, bank + ASIC3_GPIO_MASK);
	val &= ~(1 << index);
	asic3_write_register(asic, bank + ASIC3_GPIO_MASK, val);
	raw_spin_unlock_irqrestore(&asic->lock, flags);
}