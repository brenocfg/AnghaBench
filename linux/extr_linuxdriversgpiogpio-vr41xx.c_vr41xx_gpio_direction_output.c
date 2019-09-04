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
 int /*<<< orphan*/  GPIO_OUTPUT ; 
 int giu_set_direction (struct gpio_chip*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vr41xx_gpio_set (struct gpio_chip*,unsigned int,int) ; 

__attribute__((used)) static int vr41xx_gpio_direction_output(struct gpio_chip *chip, unsigned offset,
				int value)
{
	vr41xx_gpio_set(chip, offset, value);

	return giu_set_direction(chip, offset, GPIO_OUTPUT);
}