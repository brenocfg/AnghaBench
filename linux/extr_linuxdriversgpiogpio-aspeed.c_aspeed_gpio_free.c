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
struct gpio_chip {scalar_t__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  pinctrl_gpio_free (scalar_t__) ; 

__attribute__((used)) static void aspeed_gpio_free(struct gpio_chip *chip, unsigned int offset)
{
	pinctrl_gpio_free(chip->base + offset);
}