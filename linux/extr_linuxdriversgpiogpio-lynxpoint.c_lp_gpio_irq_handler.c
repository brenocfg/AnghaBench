#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_3__ {int /*<<< orphan*/  domain; } ;
struct TYPE_4__ {scalar_t__ ngpio; TYPE_1__ irq; } ;
struct lp_gpio {TYPE_2__ chip; } ;
struct irq_desc {int dummy; } ;
struct irq_data {int dummy; } ;
struct irq_chip {int /*<<< orphan*/  (* irq_eoi ) (struct irq_data*) ;} ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 scalar_t__ BIT (scalar_t__) ; 
 int /*<<< orphan*/  LP_INT_ENABLE ; 
 int /*<<< orphan*/  LP_INT_STAT ; 
 scalar_t__ __ffs (unsigned long) ; 
 int /*<<< orphan*/  generic_handle_irq (unsigned int) ; 
 struct lp_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 unsigned long inl (unsigned long) ; 
 struct irq_chip* irq_data_get_irq_chip (struct irq_data*) ; 
 struct gpio_chip* irq_desc_get_handler_data (struct irq_desc*) ; 
 struct irq_data* irq_desc_get_irq_data (struct irq_desc*) ; 
 unsigned int irq_find_mapping (int /*<<< orphan*/ ,scalar_t__) ; 
 unsigned long lp_gpio_reg (TYPE_2__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outl (scalar_t__,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct irq_data*) ; 

__attribute__((used)) static void lp_gpio_irq_handler(struct irq_desc *desc)
{
	struct irq_data *data = irq_desc_get_irq_data(desc);
	struct gpio_chip *gc = irq_desc_get_handler_data(desc);
	struct lp_gpio *lg = gpiochip_get_data(gc);
	struct irq_chip *chip = irq_data_get_irq_chip(data);
	u32 base, pin, mask;
	unsigned long reg, ena, pending;

	/* check from GPIO controller which pin triggered the interrupt */
	for (base = 0; base < lg->chip.ngpio; base += 32) {
		reg = lp_gpio_reg(&lg->chip, base, LP_INT_STAT);
		ena = lp_gpio_reg(&lg->chip, base, LP_INT_ENABLE);

		while ((pending = (inl(reg) & inl(ena)))) {
			unsigned irq;

			pin = __ffs(pending);
			mask = BIT(pin);
			/* Clear before handling so we don't lose an edge */
			outl(mask, reg);
			irq = irq_find_mapping(lg->chip.irq.domain, base + pin);
			generic_handle_irq(irq);
		}
	}
	chip->irq_eoi(data);
}