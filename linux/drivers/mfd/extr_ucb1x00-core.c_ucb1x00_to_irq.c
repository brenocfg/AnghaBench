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
struct ucb1x00 {scalar_t__ irq_base; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int ENXIO ; 
 struct ucb1x00* gpiochip_get_data (struct gpio_chip*) ; 

__attribute__((used)) static int ucb1x00_to_irq(struct gpio_chip *chip, unsigned offset)
{
	struct ucb1x00 *ucb = gpiochip_get_data(chip);

	return ucb->irq_base > 0 ? ucb->irq_base + offset : -ENXIO;
}