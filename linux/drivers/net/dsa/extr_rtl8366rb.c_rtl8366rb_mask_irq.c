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
struct realtek_smi {int /*<<< orphan*/  dev; int /*<<< orphan*/  map; } ;
struct irq_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTL8366RB_INTERRUPT_MASK_REG ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct realtek_smi* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl8366rb_get_irqmask (struct irq_data*) ; 

__attribute__((used)) static void rtl8366rb_mask_irq(struct irq_data *d)
{
	struct realtek_smi *smi = irq_data_get_irq_chip_data(d);
	int ret;

	ret = regmap_update_bits(smi->map, RTL8366RB_INTERRUPT_MASK_REG,
				 rtl8366rb_get_irqmask(d), 0);
	if (ret)
		dev_err(smi->dev, "could not mask IRQ\n");
}