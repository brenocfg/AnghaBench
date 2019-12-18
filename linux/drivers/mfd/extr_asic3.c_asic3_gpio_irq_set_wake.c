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
typedef  int u16 ;
struct irq_data {int /*<<< orphan*/  irq; } ;
struct asic3 {int dummy; } ;

/* Variables and functions */
 int ASIC3_GPIO_SLEEP_MASK ; 
 int asic3_irq_to_bank (struct asic3*,int /*<<< orphan*/ ) ; 
 int asic3_irq_to_index (struct asic3*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  asic3_set_register (struct asic3*,int,int,int) ; 
 struct asic3* irq_data_get_irq_chip_data (struct irq_data*) ; 

__attribute__((used)) static int asic3_gpio_irq_set_wake(struct irq_data *data, unsigned int on)
{
	struct asic3 *asic = irq_data_get_irq_chip_data(data);
	u32 bank, index;
	u16 bit;

	bank = asic3_irq_to_bank(asic, data->irq);
	index = asic3_irq_to_index(asic, data->irq);
	bit = 1<<index;

	asic3_set_register(asic, bank + ASIC3_GPIO_SLEEP_MASK, bit, !on);

	return 0;
}