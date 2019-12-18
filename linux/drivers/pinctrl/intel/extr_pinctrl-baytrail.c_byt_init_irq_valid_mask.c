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
struct gpio_chip {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void byt_init_irq_valid_mask(struct gpio_chip *chip,
				    unsigned long *valid_mask,
				    unsigned int ngpios)
{
	/*
	 * FIXME: currently the valid_mask is filled in as part of
	 * initializing the irq_chip below in byt_gpio_irq_init_hw().
	 * when converting this driver to the new way of passing the
	 * gpio_irq_chip along when adding the gpio_chip, move the
	 * mask initialization into this callback instead. Right now
	 * this callback is here to make sure the mask gets allocated.
	 */
}