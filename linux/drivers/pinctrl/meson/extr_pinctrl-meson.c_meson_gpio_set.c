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
 int /*<<< orphan*/  gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  meson_pinconf_set_drive (int /*<<< orphan*/ ,unsigned int,int) ; 

__attribute__((used)) static void meson_gpio_set(struct gpio_chip *chip, unsigned gpio, int value)
{
	meson_pinconf_set_drive(gpiochip_get_data(chip), gpio, value);
}