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
typedef  int u8 ;
struct rockchip_pinctrl {struct regmap* regmap_base; struct regmap* regmap_pmu; } ;
struct rockchip_pin_bank {int bank_num; struct rockchip_pinctrl* drvdata; } ;
struct regmap {int dummy; } ;

/* Variables and functions */
 int PX30_PULL_BANK_STRIDE ; 
 int PX30_PULL_BITS_PER_PIN ; 
 int PX30_PULL_GRF_OFFSET ; 
 int PX30_PULL_PINS_PER_REG ; 
 int PX30_PULL_PMU_OFFSET ; 

__attribute__((used)) static void px30_calc_pull_reg_and_bit(struct rockchip_pin_bank *bank,
				       int pin_num, struct regmap **regmap,
				       int *reg, u8 *bit)
{
	struct rockchip_pinctrl *info = bank->drvdata;

	/* The first 32 pins of the first bank are located in PMU */
	if (bank->bank_num == 0) {
		*regmap = info->regmap_pmu;
		*reg = PX30_PULL_PMU_OFFSET;
	} else {
		*regmap = info->regmap_base;
		*reg = PX30_PULL_GRF_OFFSET;

		/* correct the offset, as we're starting with the 2nd bank */
		*reg -= 0x10;
		*reg += bank->bank_num * PX30_PULL_BANK_STRIDE;
	}

	*reg += ((pin_num / PX30_PULL_PINS_PER_REG) * 4);
	*bit = (pin_num % PX30_PULL_PINS_PER_REG);
	*bit *= PX30_PULL_BITS_PER_PIN;
}