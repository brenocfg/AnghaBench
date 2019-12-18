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
struct lp_gpio {unsigned long reg_base; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int LP_CONFIG1 ; 
 int LP_CONFIG2 ; 
 struct lp_gpio* gpiochip_get_data (struct gpio_chip*) ; 

__attribute__((used)) static unsigned long lp_gpio_reg(struct gpio_chip *chip, unsigned offset,
				 int reg)
{
	struct lp_gpio *lg = gpiochip_get_data(chip);
	int reg_offset;

	if (reg == LP_CONFIG1 || reg == LP_CONFIG2)
		/* per gpio specific config registers */
		reg_offset = offset * 8;
	else
		/* bitmapped registers */
		reg_offset = (offset / 32) * 4;

	return lg->reg_base + reg + reg_offset;
}