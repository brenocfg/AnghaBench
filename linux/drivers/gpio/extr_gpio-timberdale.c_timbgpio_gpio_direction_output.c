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
 int /*<<< orphan*/  TGPIODIR ; 
 int timbgpio_update_bit (struct gpio_chip*,unsigned int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int timbgpio_gpio_direction_output(struct gpio_chip *gpio,
						unsigned nr, int val)
{
	return timbgpio_update_bit(gpio, nr, TGPIODIR, false);
}