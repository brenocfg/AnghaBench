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
struct uniphier_gpio_priv {scalar_t__ regs; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 struct uniphier_gpio_priv* gpiochip_get_data (struct gpio_chip*) ; 
 int readl (scalar_t__) ; 
 unsigned int uniphier_gpio_bank_to_reg (unsigned int) ; 
 int /*<<< orphan*/  uniphier_gpio_get_bank_and_mask (unsigned int,unsigned int*,int*) ; 

__attribute__((used)) static int uniphier_gpio_offset_read(struct gpio_chip *chip,
				     unsigned int offset, unsigned int reg)
{
	struct uniphier_gpio_priv *priv = gpiochip_get_data(chip);
	unsigned int bank, reg_offset;
	u32 mask;

	uniphier_gpio_get_bank_and_mask(offset, &bank, &mask);
	reg_offset = uniphier_gpio_bank_to_reg(bank) + reg;

	return !!(readl(priv->regs + reg_offset) & mask);
}