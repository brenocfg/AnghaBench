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
struct rdc321x_gpio {int* data_reg; int /*<<< orphan*/  reg1_data_base; int /*<<< orphan*/  reg2_data_base; int /*<<< orphan*/  sb_pdev; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 struct rdc321x_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  pci_write_config_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void rdc_gpio_set_value_impl(struct gpio_chip *chip,
				unsigned gpio, int value)
{
	struct rdc321x_gpio *gpch;
	int reg = (gpio < 32) ? 0 : 1;

	gpch = gpiochip_get_data(chip);

	if (value)
		gpch->data_reg[reg] |= 1 << (gpio & 0x1f);
	else
		gpch->data_reg[reg] &= ~(1 << (gpio & 0x1f));

	pci_write_config_dword(gpch->sb_pdev,
			reg ? gpch->reg2_data_base : gpch->reg1_data_base,
			gpch->data_reg[reg]);
}