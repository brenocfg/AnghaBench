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
 int /*<<< orphan*/  GPIO3_OD ; 
 int /*<<< orphan*/  GPIO_DIR (unsigned int) ; 
 int /*<<< orphan*/  GPIO_OD (unsigned int) ; 
 scalar_t__ PORT (unsigned int) ; 
 scalar_t__ PORT3 ; 
 int /*<<< orphan*/  PORT_PIN (unsigned int) ; 
 struct ltq_pinmux_info* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_setbit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xway_gpio_set (struct gpio_chip*,unsigned int,int) ; 

__attribute__((used)) static int xway_gpio_dir_out(struct gpio_chip *chip, unsigned int pin, int val)
{
	struct ltq_pinmux_info *info = dev_get_drvdata(chip->parent);

	if (PORT(pin) == PORT3)
		gpio_setbit(info->membase[0], GPIO3_OD, PORT_PIN(pin));
	else
		gpio_setbit(info->membase[0], GPIO_OD(pin), PORT_PIN(pin));
	gpio_setbit(info->membase[0], GPIO_DIR(pin), PORT_PIN(pin));
	xway_gpio_set(chip, pin, val);

	return 0;
}