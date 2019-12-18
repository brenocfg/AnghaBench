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
struct gpio_reg {int* irqs; scalar_t__ irqdomain; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int irq_find_mapping (scalar_t__,int) ; 
 struct gpio_reg* to_gpio_reg (struct gpio_chip*) ; 

__attribute__((used)) static int gpio_reg_to_irq(struct gpio_chip *gc, unsigned offset)
{
	struct gpio_reg *r = to_gpio_reg(gc);
	int irq = r->irqs[offset];

	if (irq >= 0 && r->irqdomain)
		irq = irq_find_mapping(r->irqdomain, irq);

	return irq;
}