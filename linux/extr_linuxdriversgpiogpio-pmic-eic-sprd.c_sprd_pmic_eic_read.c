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
typedef  scalar_t__ u16 ;
struct sprd_pmic_eic {scalar_t__ offset; int /*<<< orphan*/  map; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPRD_PMIC_EIC_BIT (unsigned int) ; 
 struct sprd_pmic_eic* gpiochip_get_data (struct gpio_chip*) ; 
 int regmap_read (int /*<<< orphan*/ ,scalar_t__,int*) ; 

__attribute__((used)) static int sprd_pmic_eic_read(struct gpio_chip *chip, unsigned int offset,
			      u16 reg)
{
	struct sprd_pmic_eic *pmic_eic = gpiochip_get_data(chip);
	u32 value;
	int ret;

	ret = regmap_read(pmic_eic->map, pmic_eic->offset + reg, &value);
	if (ret)
		return ret;

	return !!(value & BIT(SPRD_PMIC_EIC_BIT(offset)));
}