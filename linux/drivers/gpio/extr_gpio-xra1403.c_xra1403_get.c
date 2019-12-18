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
struct xra1403 {int /*<<< orphan*/  regmap; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 unsigned int BIT (unsigned int) ; 
 int /*<<< orphan*/  XRA_GSR ; 
 struct xra1403* gpiochip_get_data (struct gpio_chip*) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  to_reg (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int xra1403_get(struct gpio_chip *chip, unsigned int offset)
{
	int ret;
	unsigned int val;
	struct xra1403 *xra = gpiochip_get_data(chip);

	ret = regmap_read(xra->regmap, to_reg(XRA_GSR, offset), &val);
	if (ret)
		return ret;

	return !!(val & BIT(offset % 8));
}