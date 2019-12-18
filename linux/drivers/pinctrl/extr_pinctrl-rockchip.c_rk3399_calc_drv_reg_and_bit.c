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
typedef  int u8 ;
struct rockchip_pinctrl {struct regmap* regmap_base; struct regmap* regmap_pmu; } ;
struct rockchip_pin_bank {int bank_num; TYPE_1__* drv; struct rockchip_pinctrl* drvdata; } ;
struct regmap {int dummy; } ;
struct TYPE_2__ {int offset; scalar_t__ drv_type; } ;

/* Variables and functions */
 scalar_t__ DRV_TYPE_IO_1V8_3V0_AUTO ; 
 scalar_t__ DRV_TYPE_IO_3V3_ONLY ; 

__attribute__((used)) static void rk3399_calc_drv_reg_and_bit(struct rockchip_pin_bank *bank,
					int pin_num, struct regmap **regmap,
					int *reg, u8 *bit)
{
	struct rockchip_pinctrl *info = bank->drvdata;
	int drv_num = (pin_num / 8);

	/*  The bank0:16 and bank1:32 pins are located in PMU */
	if ((bank->bank_num == 0) || (bank->bank_num == 1))
		*regmap = info->regmap_pmu;
	else
		*regmap = info->regmap_base;

	*reg = bank->drv[drv_num].offset;
	if ((bank->drv[drv_num].drv_type == DRV_TYPE_IO_1V8_3V0_AUTO) ||
	    (bank->drv[drv_num].drv_type == DRV_TYPE_IO_3V3_ONLY))
		*bit = (pin_num % 8) * 3;
	else
		*bit = (pin_num % 8) * 2;
}