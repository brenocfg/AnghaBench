#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct gpio_mockup_chip {TYPE_1__* lines; } ;
struct gpio_chip {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dir; } ;

/* Variables and functions */
 struct gpio_mockup_chip* gpiochip_get_data (struct gpio_chip*) ; 

__attribute__((used)) static int gpio_mockup_get_direction(struct gpio_chip *gc, unsigned int offset)
{
	struct gpio_mockup_chip *chip = gpiochip_get_data(gc);

	return !chip->lines[offset].dir;
}