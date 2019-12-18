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
struct ad5592r_state {int gpio_map; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int BIT (unsigned int) ; 
 int ENODEV ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned int) ; 
 struct ad5592r_state* gpiochip_get_data (struct gpio_chip*) ; 

__attribute__((used)) static int ad5592r_gpio_request(struct gpio_chip *chip, unsigned offset)
{
	struct ad5592r_state *st = gpiochip_get_data(chip);

	if (!(st->gpio_map & BIT(offset))) {
		dev_err(st->dev, "GPIO %d is reserved by alternate function\n",
			offset);
		return -ENODEV;
	}

	return 0;
}