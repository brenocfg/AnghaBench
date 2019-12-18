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
struct stm32_pinctrl {struct regmap** irqmux; struct regmap* regmap; } ;
struct regmap {int dummy; } ;
struct reg_field {int reg; int lsb; int msb; } ;
struct device {struct device_node* of_node; } ;
struct platform_device {struct device dev; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct regmap*) ; 
 int PTR_ERR (struct regmap*) ; 
 int STM32_GPIO_PINS_PER_BANK ; 
 int SYSCFG_IRQMUX_MASK ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int,int,int,int) ; 
 struct regmap* devm_regmap_field_alloc (struct device*,struct regmap*,struct reg_field) ; 
 int fls (int) ; 
 int of_property_read_u32_index (struct device_node*,char*,int,int*) ; 
 struct regmap* syscon_regmap_lookup_by_phandle (struct device_node*,char*) ; 

__attribute__((used)) static int stm32_pctrl_dt_setup_irq(struct platform_device *pdev,
			   struct stm32_pinctrl *pctl)
{
	struct device_node *np = pdev->dev.of_node;
	struct device *dev = &pdev->dev;
	struct regmap *rm;
	int offset, ret, i;
	int mask, mask_width;

	pctl->regmap = syscon_regmap_lookup_by_phandle(np, "st,syscfg");
	if (IS_ERR(pctl->regmap))
		return PTR_ERR(pctl->regmap);

	rm = pctl->regmap;

	ret = of_property_read_u32_index(np, "st,syscfg", 1, &offset);
	if (ret)
		return ret;

	ret = of_property_read_u32_index(np, "st,syscfg", 2, &mask);
	if (ret)
		mask = SYSCFG_IRQMUX_MASK;

	mask_width = fls(mask);

	for (i = 0; i < STM32_GPIO_PINS_PER_BANK; i++) {
		struct reg_field mux;

		mux.reg = offset + (i / 4) * 4;
		mux.lsb = (i % 4) * mask_width;
		mux.msb = mux.lsb + mask_width - 1;

		dev_dbg(dev, "irqmux%d: reg:%#x, lsb:%d, msb:%d\n",
			i, mux.reg, mux.lsb, mux.msb);

		pctl->irqmux[i] = devm_regmap_field_alloc(dev, rm, mux);
		if (IS_ERR(pctl->irqmux[i]))
			return PTR_ERR(pctl->irqmux[i]);
	}

	return 0;
}