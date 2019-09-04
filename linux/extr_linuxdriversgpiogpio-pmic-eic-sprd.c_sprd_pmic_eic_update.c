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
typedef  unsigned int u32 ;
typedef  scalar_t__ u16 ;
struct sprd_pmic_eic {scalar_t__ offset; int /*<<< orphan*/  map; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (unsigned int) ; 
 unsigned int SPRD_PMIC_EIC_BIT (unsigned int) ; 
 struct sprd_pmic_eic* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void sprd_pmic_eic_update(struct gpio_chip *chip, unsigned int offset,
				 u16 reg, unsigned int val)
{
	struct sprd_pmic_eic *pmic_eic = gpiochip_get_data(chip);
	u32 shift = SPRD_PMIC_EIC_BIT(offset);

	regmap_update_bits(pmic_eic->map, pmic_eic->offset + reg,
			   BIT(shift), val << shift);
}