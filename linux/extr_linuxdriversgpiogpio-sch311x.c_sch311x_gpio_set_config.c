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
typedef  int /*<<< orphan*/  u8 ;
struct sch311x_gpio_block {int /*<<< orphan*/  lock; scalar_t__* config_regs; scalar_t__ runtime_reg; } ;
struct gpio_chip {int dummy; } ;
typedef  enum pin_config_param { ____Placeholder_pin_config_param } pin_config_param ;

/* Variables and functions */
 int ENOTSUPP ; 
#define  PIN_CONFIG_DRIVE_OPEN_DRAIN 129 
#define  PIN_CONFIG_DRIVE_PUSH_PULL 128 
 int /*<<< orphan*/  SCH311X_GPIO_CONF_OPEN_DRAIN ; 
 struct sch311x_gpio_block* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  inb (scalar_t__) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 
 int pinconf_to_config_param (unsigned long) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sch311x_gpio_set_config(struct gpio_chip *chip, unsigned offset,
				   unsigned long config)
{
	struct sch311x_gpio_block *block = gpiochip_get_data(chip);
	enum pin_config_param param = pinconf_to_config_param(config);
	u8 data;

	switch (param) {
	case PIN_CONFIG_DRIVE_OPEN_DRAIN:
		spin_lock(&block->lock);
		data = inb(block->runtime_reg + block->config_regs[offset]);
		data |= SCH311X_GPIO_CONF_OPEN_DRAIN;
		outb(data, block->runtime_reg + block->config_regs[offset]);
		spin_unlock(&block->lock);
		return 0;
	case PIN_CONFIG_DRIVE_PUSH_PULL:
		spin_lock(&block->lock);
		data = inb(block->runtime_reg + block->config_regs[offset]);
		data &= ~SCH311X_GPIO_CONF_OPEN_DRAIN;
		outb(data, block->runtime_reg + block->config_regs[offset]);
		spin_unlock(&block->lock);
		return 0;
	default:
		break;
	}
	return -ENOTSUPP;
}