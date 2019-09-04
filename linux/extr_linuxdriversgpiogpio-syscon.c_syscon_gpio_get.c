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
struct gpio_chip {int dummy; } ;
struct TYPE_2__ {unsigned int dat_bit_offset; } ;

/* Variables and functions */
 unsigned int BIT (unsigned int) ; 
 unsigned int SYSCON_REG_BITS ; 
 unsigned int SYSCON_REG_SIZE ; 
 struct syscon_gpio_priv* gpiochip_get_data (struct gpio_chip*) ; 
 int regmap_read (int /*<<< orphan*/ ,unsigned int,unsigned int*) ; 

__attribute__((used)) static int syscon_gpio_get(struct gpio_chip *chip, unsigned offset)
{
	struct syscon_gpio_priv *priv = gpiochip_get_data(chip);
	unsigned int val, offs;
	int ret;

	offs = priv->dreg_offset + priv->data->dat_bit_offset + offset;

	ret = regmap_read(priv->syscon,
			  (offs / SYSCON_REG_BITS) * SYSCON_REG_SIZE, &val);
	if (ret)
		return ret;

	return !!(val & BIT(offs % SYSCON_REG_BITS));
}