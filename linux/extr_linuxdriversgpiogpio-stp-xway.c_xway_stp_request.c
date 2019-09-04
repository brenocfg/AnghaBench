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
struct xway_stp {int reserved; } ;
struct gpio_chip {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int BIT (unsigned int) ; 
 int ENODEV ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned int) ; 
 struct xway_stp* gpiochip_get_data (struct gpio_chip*) ; 

__attribute__((used)) static int xway_stp_request(struct gpio_chip *gc, unsigned gpio)
{
	struct xway_stp *chip = gpiochip_get_data(gc);

	if ((gpio < 8) && (chip->reserved & BIT(gpio))) {
		dev_err(gc->parent, "GPIO %d is driven by hardware\n", gpio);
		return -ENODEV;
	}

	return 0;
}