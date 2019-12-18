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
struct wcove_gpio {int /*<<< orphan*/  regmap; scalar_t__ set_irq_mask; } ;

/* Variables and functions */
 unsigned int BIT (int) ; 
 int GROUP0_NR_IRQS ; 
 int GROUP1_NR_IRQS ; 
 int IRQ_MASK_BASE ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,unsigned int,unsigned int,unsigned int) ; 

__attribute__((used)) static void wcove_update_irq_mask(struct wcove_gpio *wg, int gpio)
{
	unsigned int reg, mask;

	if (gpio < GROUP0_NR_IRQS) {
		reg = IRQ_MASK_BASE;
		mask = BIT(gpio % GROUP0_NR_IRQS);
	} else {
		reg = IRQ_MASK_BASE + 1;
		mask = BIT((gpio - GROUP0_NR_IRQS) % GROUP1_NR_IRQS);
	}

	if (wg->set_irq_mask)
		regmap_update_bits(wg->regmap, reg, mask, mask);
	else
		regmap_update_bits(wg->regmap, reg, mask, 0);
}