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
struct rdc321x_gpio {int reg1_data_base; int reg2_data_base; int /*<<< orphan*/  lock; int /*<<< orphan*/  sb_pdev; int /*<<< orphan*/ * data_reg; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 struct rdc321x_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  pci_read_config_dword (int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  pci_write_config_dword (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rdc_gpio_get_value(struct gpio_chip *chip, unsigned gpio)
{
	struct rdc321x_gpio *gpch;
	u32 value = 0;
	int reg;

	gpch = gpiochip_get_data(chip);
	reg = gpio < 32 ? gpch->reg1_data_base : gpch->reg2_data_base;

	spin_lock(&gpch->lock);
	pci_write_config_dword(gpch->sb_pdev, reg,
					gpch->data_reg[gpio < 32 ? 0 : 1]);
	pci_read_config_dword(gpch->sb_pdev, reg, &value);
	spin_unlock(&gpch->lock);

	return (1 << (gpio & 0x1f)) & value ? 1 : 0;
}