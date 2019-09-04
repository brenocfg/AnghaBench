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
typedef  int /*<<< orphan*/  u32 ;
struct uniphier_gpio_priv {int dummy; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 struct uniphier_gpio_priv* gpiochip_get_data (struct gpio_chip*) ; 
 scalar_t__ uniphier_gpio_bank_to_reg (unsigned int) ; 
 int /*<<< orphan*/  uniphier_gpio_reg_update (struct uniphier_gpio_priv*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void uniphier_gpio_bank_write(struct gpio_chip *chip, unsigned int bank,
				     unsigned int reg, u32 mask, u32 val)
{
	struct uniphier_gpio_priv *priv = gpiochip_get_data(chip);

	if (!mask)
		return;

	uniphier_gpio_reg_update(priv, uniphier_gpio_bank_to_reg(bank) + reg,
				 mask, val);
}