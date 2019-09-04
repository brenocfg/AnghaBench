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
struct syscon_gpio_priv {unsigned int dir_reg_offset; TYPE_1__* data; int /*<<< orphan*/  syscon; } ;
struct gpio_chip {int dummy; } ;
struct TYPE_2__ {int flags; unsigned int dir_bit_offset; int /*<<< orphan*/  (* set ) (struct gpio_chip*,unsigned int,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (unsigned int) ; 
 int GPIO_SYSCON_FEAT_DIR ; 
 unsigned int SYSCON_REG_BITS ; 
 unsigned int SYSCON_REG_SIZE ; 
 struct syscon_gpio_priv* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct gpio_chip*,unsigned int,int) ; 

__attribute__((used)) static int syscon_gpio_dir_out(struct gpio_chip *chip, unsigned offset, int val)
{
	struct syscon_gpio_priv *priv = gpiochip_get_data(chip);

	if (priv->data->flags & GPIO_SYSCON_FEAT_DIR) {
		unsigned int offs;

		offs = priv->dir_reg_offset +
		       priv->data->dir_bit_offset + offset;

		regmap_update_bits(priv->syscon,
				   (offs / SYSCON_REG_BITS) * SYSCON_REG_SIZE,
				   BIT(offs % SYSCON_REG_BITS),
				   BIT(offs % SYSCON_REG_BITS));
	}

	priv->data->set(chip, offset, val);

	return 0;
}