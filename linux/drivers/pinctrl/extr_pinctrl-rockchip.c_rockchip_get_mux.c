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
typedef  unsigned int u8 ;
struct rockchip_pinctrl {struct regmap* regmap_base; struct regmap* regmap_pmu; int /*<<< orphan*/  dev; } ;
struct rockchip_pin_bank {int recalced_mask; TYPE_1__* iomux; struct rockchip_pinctrl* drvdata; } ;
struct regmap {int dummy; } ;
struct TYPE_2__ {int type; int offset; } ;

/* Variables and functions */
 int BIT (int) ; 
 int EINVAL ; 
 int IOMUX_GPIO_ONLY ; 
 int IOMUX_SOURCE_PMU ; 
 int IOMUX_UNROUTED ; 
 int IOMUX_WIDTH_3BIT ; 
 int IOMUX_WIDTH_4BIT ; 
 int RK_FUNC_GPIO ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int regmap_read (struct regmap*,int,unsigned int*) ; 
 int /*<<< orphan*/  rockchip_get_recalced_mux (struct rockchip_pin_bank*,int,int*,unsigned int*,int*) ; 

__attribute__((used)) static int rockchip_get_mux(struct rockchip_pin_bank *bank, int pin)
{
	struct rockchip_pinctrl *info = bank->drvdata;
	int iomux_num = (pin / 8);
	struct regmap *regmap;
	unsigned int val;
	int reg, ret, mask, mux_type;
	u8 bit;

	if (iomux_num > 3)
		return -EINVAL;

	if (bank->iomux[iomux_num].type & IOMUX_UNROUTED) {
		dev_err(info->dev, "pin %d is unrouted\n", pin);
		return -EINVAL;
	}

	if (bank->iomux[iomux_num].type & IOMUX_GPIO_ONLY)
		return RK_FUNC_GPIO;

	regmap = (bank->iomux[iomux_num].type & IOMUX_SOURCE_PMU)
				? info->regmap_pmu : info->regmap_base;

	/* get basic quadrupel of mux registers and the correct reg inside */
	mux_type = bank->iomux[iomux_num].type;
	reg = bank->iomux[iomux_num].offset;
	if (mux_type & IOMUX_WIDTH_4BIT) {
		if ((pin % 8) >= 4)
			reg += 0x4;
		bit = (pin % 4) * 4;
		mask = 0xf;
	} else if (mux_type & IOMUX_WIDTH_3BIT) {
		if ((pin % 8) >= 5)
			reg += 0x4;
		bit = (pin % 8 % 5) * 3;
		mask = 0x7;
	} else {
		bit = (pin % 8) * 2;
		mask = 0x3;
	}

	if (bank->recalced_mask & BIT(pin))
		rockchip_get_recalced_mux(bank, pin, &reg, &bit, &mask);

	ret = regmap_read(regmap, reg, &val);
	if (ret)
		return ret;

	return ((val >> bit) & mask);
}