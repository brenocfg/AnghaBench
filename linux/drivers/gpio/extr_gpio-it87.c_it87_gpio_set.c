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
typedef  int u8 ;
typedef  scalar_t__ u16 ;
struct it87_gpio {scalar_t__ io_base; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 struct it87_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 int inb (scalar_t__) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 

__attribute__((used)) static void it87_gpio_set(struct gpio_chip *chip,
			  unsigned gpio_num, int val)
{
	u8 mask, curr_vals;
	u16 reg;
	struct it87_gpio *it87_gpio = gpiochip_get_data(chip);

	mask = 1 << (gpio_num % 8);
	reg = (gpio_num / 8) + it87_gpio->io_base;

	curr_vals = inb(reg);
	if (val)
		outb(curr_vals | mask, reg);
	else
		outb(curr_vals & ~mask, reg);
}