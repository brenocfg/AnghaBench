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
typedef  int u32 ;
struct rdc321x_gpio {int /*<<< orphan*/  lock; int /*<<< orphan*/  reg2_ctrl_base; int /*<<< orphan*/  reg1_ctrl_base; int /*<<< orphan*/  sb_pdev; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 struct rdc321x_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 int pci_read_config_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int pci_write_config_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rdc_gpio_set_value_impl (struct gpio_chip*,unsigned int,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rdc_gpio_config(struct gpio_chip *chip,
				unsigned gpio, int value)
{
	struct rdc321x_gpio *gpch;
	int err;
	u32 reg;

	gpch = gpiochip_get_data(chip);

	spin_lock(&gpch->lock);
	err = pci_read_config_dword(gpch->sb_pdev, gpio < 32 ?
			gpch->reg1_ctrl_base : gpch->reg2_ctrl_base, &reg);
	if (err)
		goto unlock;

	reg |= 1 << (gpio & 0x1f);

	err = pci_write_config_dword(gpch->sb_pdev, gpio < 32 ?
			gpch->reg1_ctrl_base : gpch->reg2_ctrl_base, reg);
	if (err)
		goto unlock;

	rdc_gpio_set_value_impl(chip, gpio, value);

unlock:
	spin_unlock(&gpch->lock);

	return err;
}