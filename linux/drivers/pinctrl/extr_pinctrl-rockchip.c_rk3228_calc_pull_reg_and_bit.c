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
struct rockchip_pinctrl {struct regmap* regmap_base; } ;
struct rockchip_pin_bank {int bank_num; struct rockchip_pinctrl* drvdata; } ;
struct regmap {int dummy; } ;

/* Variables and functions */
 int RK3188_PULL_BANK_STRIDE ; 
 int RK3188_PULL_BITS_PER_PIN ; 
 int RK3188_PULL_PINS_PER_REG ; 
 int RK3228_PULL_OFFSET ; 

__attribute__((used)) static void rk3228_calc_pull_reg_and_bit(struct rockchip_pin_bank *bank,
				    int pin_num, struct regmap **regmap,
				    int *reg, u8 *bit)
{
	struct rockchip_pinctrl *info = bank->drvdata;

	*regmap = info->regmap_base;
	*reg = RK3228_PULL_OFFSET;
	*reg += bank->bank_num * RK3188_PULL_BANK_STRIDE;
	*reg += ((pin_num / RK3188_PULL_PINS_PER_REG) * 4);

	*bit = (pin_num % RK3188_PULL_PINS_PER_REG);
	*bit *= RK3188_PULL_BITS_PER_PIN;
}