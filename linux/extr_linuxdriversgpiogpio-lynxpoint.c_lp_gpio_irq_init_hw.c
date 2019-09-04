#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned int ngpio; } ;
struct lp_gpio {TYPE_1__ chip; } ;

/* Variables and functions */
 int /*<<< orphan*/  LP_INT_ENABLE ; 
 int /*<<< orphan*/  LP_INT_STAT ; 
 unsigned long lp_gpio_reg (TYPE_1__*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outl (int,unsigned long) ; 

__attribute__((used)) static void lp_gpio_irq_init_hw(struct lp_gpio *lg)
{
	unsigned long reg;
	unsigned base;

	for (base = 0; base < lg->chip.ngpio; base += 32) {
		/* disable gpio pin interrupts */
		reg = lp_gpio_reg(&lg->chip, base, LP_INT_ENABLE);
		outl(0, reg);
		/* Clear interrupt status register */
		reg = lp_gpio_reg(&lg->chip, base, LP_INT_STAT);
		outl(0xffffffff, reg);
	}
}