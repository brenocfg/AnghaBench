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
struct st_retime_packed {void* double_edge; void* clknotdata; void* retime; void* invertclk; void* delay_1; void* delay_0; void* clk1notclk0; } ;
struct TYPE_2__ {struct st_retime_packed rt_p; } ;
struct st_pio_control {TYPE_1__ rt; } ;
struct st_pinctrl {struct st_pctl_data* data; struct regmap* regmap; struct device* dev; } ;
struct st_pctl_data {int rt; } ;
struct regmap {int dummy; } ;
struct reg_field {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (void*) ; 
 struct reg_field RT_P_CFG0_CLK1NOTCLK0_FIELD (int) ; 
 struct reg_field RT_P_CFG0_DELAY_0_FIELD (int) ; 
 struct reg_field RT_P_CFG0_DELAY_1_FIELD (int) ; 
 struct reg_field RT_P_CFG1_CLKNOTDATA_FIELD (int) ; 
 struct reg_field RT_P_CFG1_DOUBLE_EDGE_FIELD (int) ; 
 struct reg_field RT_P_CFG1_INVERTCLK_FIELD (int) ; 
 struct reg_field RT_P_CFG1_RETIME_FIELD (int) ; 
 int RT_P_CFGS_PER_BANK ; 
 void* devm_regmap_field_alloc (struct device*,struct regmap*,struct reg_field) ; 

__attribute__((used)) static int st_pctl_dt_setup_retime_packed(struct st_pinctrl *info,
	int bank, struct st_pio_control *pc)
{
	struct device *dev = info->dev;
	struct regmap *rm = info->regmap;
	const struct st_pctl_data *data = info->data;
	/* 2 registers per bank */
	int reg = (data->rt + bank * RT_P_CFGS_PER_BANK) * 4;
	struct st_retime_packed *rt_p = &pc->rt.rt_p;
	/* cfg0 */
	struct reg_field clk1notclk0 = RT_P_CFG0_CLK1NOTCLK0_FIELD(reg);
	struct reg_field delay_0 = RT_P_CFG0_DELAY_0_FIELD(reg);
	struct reg_field delay_1 = RT_P_CFG0_DELAY_1_FIELD(reg);
	/* cfg1 */
	struct reg_field invertclk = RT_P_CFG1_INVERTCLK_FIELD(reg + 4);
	struct reg_field retime = RT_P_CFG1_RETIME_FIELD(reg + 4);
	struct reg_field clknotdata = RT_P_CFG1_CLKNOTDATA_FIELD(reg + 4);
	struct reg_field double_edge = RT_P_CFG1_DOUBLE_EDGE_FIELD(reg + 4);

	rt_p->clk1notclk0 = devm_regmap_field_alloc(dev, rm, clk1notclk0);
	rt_p->delay_0	= devm_regmap_field_alloc(dev, rm, delay_0);
	rt_p->delay_1 = devm_regmap_field_alloc(dev, rm, delay_1);
	rt_p->invertclk = devm_regmap_field_alloc(dev, rm, invertclk);
	rt_p->retime = devm_regmap_field_alloc(dev, rm, retime);
	rt_p->clknotdata = devm_regmap_field_alloc(dev, rm, clknotdata);
	rt_p->double_edge = devm_regmap_field_alloc(dev, rm, double_edge);

	if (IS_ERR(rt_p->clk1notclk0) || IS_ERR(rt_p->delay_0) ||
		 IS_ERR(rt_p->delay_1) || IS_ERR(rt_p->invertclk) ||
		 IS_ERR(rt_p->retime) || IS_ERR(rt_p->clknotdata) ||
		 IS_ERR(rt_p->double_edge))
		return -EINVAL;

	return 0;
}