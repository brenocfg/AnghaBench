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
struct egpio_chip {int /*<<< orphan*/  is_out; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  egpio_set (struct gpio_chip*,unsigned int,int) ; 
 struct egpio_chip* gpiochip_get_data (struct gpio_chip*) ; 
 scalar_t__ test_bit (unsigned int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int egpio_direction_output(struct gpio_chip *chip,
					unsigned offset, int value)
{
	struct egpio_chip *egpio;

	egpio = gpiochip_get_data(chip);
	if (test_bit(offset, &egpio->is_out)) {
		egpio_set(chip, offset, value);
		return 0;
	} else {
		return -EINVAL;
	}
}