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
struct gpio_mockup_chip {int /*<<< orphan*/  irqsim; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 struct gpio_mockup_chip* gpiochip_get_data (struct gpio_chip*) ; 
 int irq_sim_irqnum (int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static int gpio_mockup_to_irq(struct gpio_chip *gc, unsigned int offset)
{
	struct gpio_mockup_chip *chip = gpiochip_get_data(gc);

	return irq_sim_irqnum(&chip->irqsim, offset);
}