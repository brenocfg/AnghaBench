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
typedef  int u32 ;
struct rockchip_pinctrl {struct regmap* regmap_base; struct regmap* regmap_pmu; int /*<<< orphan*/  dev; } ;
struct rockchip_pin_bank {int recalced_mask; int route_mask; TYPE_1__* iomux; int /*<<< orphan*/  bank_num; struct rockchip_pinctrl* drvdata; } ;
struct regmap {int dummy; } ;
struct TYPE_2__ {int type; int offset; } ;

/* Variables and functions */
 int BIT (int) ; 
 int IOMUX_GPIO_ONLY ; 
 int IOMUX_SOURCE_PMU ; 
 int IOMUX_WIDTH_3BIT ; 
 int IOMUX_WIDTH_4BIT ; 
#define  ROCKCHIP_ROUTE_GRF 129 
#define  ROCKCHIP_ROUTE_PMU 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int) ; 
 int regmap_update_bits (struct regmap*,int,int,int) ; 
 int regmap_write (struct regmap*,int,int) ; 
 scalar_t__ rockchip_get_mux_route (struct rockchip_pin_bank*,int,int,int*,int*,int*) ; 
 int /*<<< orphan*/  rockchip_get_recalced_mux (struct rockchip_pin_bank*,int,int*,int*,int*) ; 
 int rockchip_verify_mux (struct rockchip_pin_bank*,int,int) ; 

__attribute__((used)) static int rockchip_set_mux(struct rockchip_pin_bank *bank, int pin, int mux)
{
	struct rockchip_pinctrl *info = bank->drvdata;
	int iomux_num = (pin / 8);
	struct regmap *regmap;
	int reg, ret, mask, mux_type;
	u8 bit;
	u32 data, rmask, route_location, route_reg, route_val;

	ret = rockchip_verify_mux(bank, pin, mux);
	if (ret < 0)
		return ret;

	if (bank->iomux[iomux_num].type & IOMUX_GPIO_ONLY)
		return 0;

	dev_dbg(info->dev, "setting mux of GPIO%d-%d to %d\n",
						bank->bank_num, pin, mux);

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

	if (bank->route_mask & BIT(pin)) {
		if (rockchip_get_mux_route(bank, pin, mux, &route_location,
					   &route_reg, &route_val)) {
			struct regmap *route_regmap = regmap;

			/* handle special locations */
			switch (route_location) {
			case ROCKCHIP_ROUTE_PMU:
				route_regmap = info->regmap_pmu;
				break;
			case ROCKCHIP_ROUTE_GRF:
				route_regmap = info->regmap_base;
				break;
			}

			ret = regmap_write(route_regmap, route_reg, route_val);
			if (ret)
				return ret;
		}
	}

	data = (mask << (bit + 16));
	rmask = data | (data >> 16);
	data |= (mux & mask) << bit;
	ret = regmap_update_bits(regmap, reg, rmask, data);

	return ret;
}