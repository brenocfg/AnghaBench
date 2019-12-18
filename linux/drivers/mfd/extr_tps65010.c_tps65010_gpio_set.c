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
 int /*<<< orphan*/  OFF ; 
 int /*<<< orphan*/  ON ; 
 int /*<<< orphan*/  tps65010_set_gpio_out_value (unsigned int,int) ; 
 int /*<<< orphan*/  tps65010_set_led (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tps65010_set_vib (int) ; 

__attribute__((used)) static void
tps65010_gpio_set(struct gpio_chip *chip, unsigned offset, int value)
{
	if (offset < 4)
		tps65010_set_gpio_out_value(offset + 1, value);
	else if (offset < 6)
		tps65010_set_led(offset - 3, value ? ON : OFF);
	else
		tps65010_set_vib(value);
}