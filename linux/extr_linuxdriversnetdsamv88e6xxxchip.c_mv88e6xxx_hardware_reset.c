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
struct mv88e6xxx_chip {struct gpio_desc* reset; } ;
struct gpio_desc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpiod_set_value_cansleep (struct gpio_desc*,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void mv88e6xxx_hardware_reset(struct mv88e6xxx_chip *chip)
{
	struct gpio_desc *gpiod = chip->reset;

	/* If there is a GPIO connected to the reset pin, toggle it */
	if (gpiod) {
		gpiod_set_value_cansleep(gpiod, 1);
		usleep_range(10000, 20000);
		gpiod_set_value_cansleep(gpiod, 0);
		usleep_range(10000, 20000);
	}
}