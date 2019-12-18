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
struct nsp_gpio {int /*<<< orphan*/  irq_domain; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 struct nsp_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 int irq_linear_revmap (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int nsp_gpio_to_irq(struct gpio_chip *gc, unsigned offset)
{
	struct nsp_gpio *chip = gpiochip_get_data(gc);

	return irq_linear_revmap(chip->irq_domain, offset);
}