#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct syscon_gpio_priv {unsigned int dreg_offset; int /*<<< orphan*/  syscon; TYPE_1__* data; } ;
struct gpio_chip {int /*<<< orphan*/  parent; } ;
struct TYPE_2__ {unsigned int dat_bit_offset; } ;

/* Variables and functions */
 int BIT (unsigned int) ; 
 int KEYSTONE_LOCK_BIT ; 
 unsigned int SYSCON_REG_BITS ; 
 unsigned int SYSCON_REG_SIZE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 struct syscon_gpio_priv* gpiochip_get_data (struct gpio_chip*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,unsigned int,int,int) ; 

__attribute__((used)) static void keystone_gpio_set(struct gpio_chip *chip, unsigned offset, int val)
{
	struct syscon_gpio_priv *priv = gpiochip_get_data(chip);
	unsigned int offs;
	int ret;

	offs = priv->dreg_offset + priv->data->dat_bit_offset + offset;

	if (!val)
		return;

	ret = regmap_update_bits(
			priv->syscon,
			(offs / SYSCON_REG_BITS) * SYSCON_REG_SIZE,
			BIT(offs % SYSCON_REG_BITS) | KEYSTONE_LOCK_BIT,
			BIT(offs % SYSCON_REG_BITS) | KEYSTONE_LOCK_BIT);
	if (ret < 0)
		dev_err(chip->parent, "gpio write failed ret(%d)\n", ret);
}