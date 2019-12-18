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
struct ltq_pinmux_info {int /*<<< orphan*/ * membase; } ;
struct gpio_chip {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIO_OUT (unsigned int) ; 
 int /*<<< orphan*/  PORT_PIN (unsigned int) ; 
 struct ltq_pinmux_info* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_clearbit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_setbit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xway_gpio_set(struct gpio_chip *chip, unsigned int pin, int val)
{
	struct ltq_pinmux_info *info = dev_get_drvdata(chip->parent);

	if (val)
		gpio_setbit(info->membase[0], GPIO_OUT(pin), PORT_PIN(pin));
	else
		gpio_clearbit(info->membase[0], GPIO_OUT(pin), PORT_PIN(pin));
}