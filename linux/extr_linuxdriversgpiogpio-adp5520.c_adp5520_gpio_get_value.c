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
typedef  int uint8_t ;
struct gpio_chip {int dummy; } ;
struct adp5520_gpio {int* lut; int /*<<< orphan*/  master; int /*<<< orphan*/  output; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADP5520_GPIO_IN ; 
 int /*<<< orphan*/  ADP5520_GPIO_OUT ; 
 int /*<<< orphan*/  adp5520_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 struct adp5520_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 scalar_t__ test_bit (unsigned int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int adp5520_gpio_get_value(struct gpio_chip *chip, unsigned off)
{
	struct adp5520_gpio *dev;
	uint8_t reg_val;

	dev = gpiochip_get_data(chip);

	/*
	 * There are dedicated registers for GPIO IN/OUT.
	 * Make sure we return the right value, even when configured as output
	 */

	if (test_bit(off, &dev->output))
		adp5520_read(dev->master, ADP5520_GPIO_OUT, &reg_val);
	else
		adp5520_read(dev->master, ADP5520_GPIO_IN, &reg_val);

	return !!(reg_val & dev->lut[off]);
}