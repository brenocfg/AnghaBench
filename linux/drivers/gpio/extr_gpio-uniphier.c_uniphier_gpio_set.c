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
 int /*<<< orphan*/  UNIPHIER_GPIO_PORT_DATA ; 
 int /*<<< orphan*/  uniphier_gpio_offset_write (struct gpio_chip*,unsigned int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void uniphier_gpio_set(struct gpio_chip *chip,
			      unsigned int offset, int val)
{
	uniphier_gpio_offset_write(chip, offset, UNIPHIER_GPIO_PORT_DATA, val);
}