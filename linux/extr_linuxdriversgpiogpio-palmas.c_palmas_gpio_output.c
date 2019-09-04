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
struct palmas_gpio {struct palmas* palmas; } ;
struct palmas {int dummy; } ;
struct gpio_chip {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (unsigned int) ; 
 int /*<<< orphan*/  PALMAS_GPIO_BASE ; 
 unsigned int PALMAS_GPIO_DATA_DIR ; 
 unsigned int PALMAS_GPIO_DATA_DIR2 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned int,int) ; 
 struct palmas_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  palmas_gpio_set (struct gpio_chip*,unsigned int,int) ; 
 int palmas_update_bits (struct palmas*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int palmas_gpio_output(struct gpio_chip *gc, unsigned offset,
				int value)
{
	struct palmas_gpio *pg = gpiochip_get_data(gc);
	struct palmas *palmas = pg->palmas;
	int ret;
	unsigned int reg;
	int gpio16 = (offset/8);

	offset %= 8;
	reg = (gpio16) ? PALMAS_GPIO_DATA_DIR2 : PALMAS_GPIO_DATA_DIR;

	/* Set the initial value */
	palmas_gpio_set(gc, offset, value);

	ret = palmas_update_bits(palmas, PALMAS_GPIO_BASE, reg,
				BIT(offset), BIT(offset));
	if (ret < 0)
		dev_err(gc->parent, "Reg 0x%02x update failed, %d\n", reg,
			ret);
	return ret;
}