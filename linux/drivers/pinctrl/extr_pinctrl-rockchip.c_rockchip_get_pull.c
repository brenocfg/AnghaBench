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
typedef  int u32 ;
struct rockchip_pinctrl {int /*<<< orphan*/  dev; struct rockchip_pin_ctrl* ctrl; } ;
struct rockchip_pin_ctrl {int type; int /*<<< orphan*/  (* pull_calc_reg ) (struct rockchip_pin_bank*,int,struct regmap**,int*,int*) ;} ;
struct rockchip_pin_bank {int* pull_type; struct rockchip_pinctrl* drvdata; } ;
struct regmap {int dummy; } ;

/* Variables and functions */
 int BIT (int) ; 
 int EINVAL ; 
 int PIN_CONFIG_BIAS_DISABLE ; 
 int PIN_CONFIG_BIAS_PULL_PIN_DEFAULT ; 
#define  PX30 135 
#define  RK2928 134 
 int RK3066B ; 
#define  RK3128 133 
#define  RK3188 132 
 int RK3188_PULL_BITS_PER_PIN ; 
#define  RK3288 131 
#define  RK3368 130 
#define  RK3399 129 
#define  RV1108 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int regmap_read (struct regmap*,int,int*) ; 
 int** rockchip_pull_list ; 
 int /*<<< orphan*/  stub1 (struct rockchip_pin_bank*,int,struct regmap**,int*,int*) ; 

__attribute__((used)) static int rockchip_get_pull(struct rockchip_pin_bank *bank, int pin_num)
{
	struct rockchip_pinctrl *info = bank->drvdata;
	struct rockchip_pin_ctrl *ctrl = info->ctrl;
	struct regmap *regmap;
	int reg, ret, pull_type;
	u8 bit;
	u32 data;

	/* rk3066b does support any pulls */
	if (ctrl->type == RK3066B)
		return PIN_CONFIG_BIAS_DISABLE;

	ctrl->pull_calc_reg(bank, pin_num, &regmap, &reg, &bit);

	ret = regmap_read(regmap, reg, &data);
	if (ret)
		return ret;

	switch (ctrl->type) {
	case RK2928:
	case RK3128:
		return !(data & BIT(bit))
				? PIN_CONFIG_BIAS_PULL_PIN_DEFAULT
				: PIN_CONFIG_BIAS_DISABLE;
	case PX30:
	case RV1108:
	case RK3188:
	case RK3288:
	case RK3368:
	case RK3399:
		pull_type = bank->pull_type[pin_num / 8];
		data >>= bit;
		data &= (1 << RK3188_PULL_BITS_PER_PIN) - 1;

		return rockchip_pull_list[pull_type][data];
	default:
		dev_err(info->dev, "unsupported pinctrl type\n");
		return -EINVAL;
	};
}