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
struct gpio_chip {scalar_t__ base; int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  pinctrl_gpio_free (scalar_t__) ; 

__attribute__((used)) static void npcmgpio_gpio_free(struct gpio_chip *chip, unsigned int offset)
{
	dev_dbg(chip->parent, "gpio_free: offset%d\n", offset);
	pinctrl_gpio_free(offset + chip->base);
}