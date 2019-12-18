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
 int cp2112_gpio_get_all (struct gpio_chip*) ; 

__attribute__((used)) static int cp2112_gpio_get(struct gpio_chip *chip, unsigned int offset)
{
	int ret;

	ret = cp2112_gpio_get_all(chip);
	if (ret < 0)
		return ret;

	return (ret >> offset) & 1;
}