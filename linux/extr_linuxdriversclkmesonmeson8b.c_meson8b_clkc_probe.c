#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct regmap {int dummy; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct TYPE_6__ {struct regmap* map; } ;
struct TYPE_5__ {int /*<<< orphan*/ * hws; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_2__**) ; 
 int CLKID_XTAL ; 
 int CLK_NR_CLKS ; 
 int ENXIO ; 
 scalar_t__ IS_ERR (struct regmap*) ; 
 int PTR_ERR (struct regmap*) ; 
 int /*<<< orphan*/  clk_base ; 
 int /*<<< orphan*/  clkc_regmap_config ; 
 int devm_clk_hw_register (struct device*,int /*<<< orphan*/ ) ; 
 int devm_of_clk_add_hw_provider (struct device*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 struct regmap* devm_regmap_init_mmio (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_2__** meson8b_clk_regmaps ; 
 TYPE_1__ meson8b_hw_onecell_data ; 
 int /*<<< orphan*/  of_clk_hw_onecell_get ; 

__attribute__((used)) static int meson8b_clkc_probe(struct platform_device *pdev)
{
	int ret, i;
	struct device *dev = &pdev->dev;
	struct regmap *map;

	if (!clk_base)
		return -ENXIO;

	map = devm_regmap_init_mmio(dev, clk_base, &clkc_regmap_config);
	if (IS_ERR(map))
		return PTR_ERR(map);

	/* Populate regmap for the regmap backed clocks */
	for (i = 0; i < ARRAY_SIZE(meson8b_clk_regmaps); i++)
		meson8b_clk_regmaps[i]->map = map;

	/*
	 * register all clks
	 * CLKID_UNUSED = 0, so skip it and start with CLKID_XTAL = 1
	 */
	for (i = CLKID_XTAL; i < CLK_NR_CLKS; i++) {
		/* array might be sparse */
		if (!meson8b_hw_onecell_data.hws[i])
			continue;

		ret = devm_clk_hw_register(dev, meson8b_hw_onecell_data.hws[i]);
		if (ret)
			return ret;
	}

	return devm_of_clk_add_hw_provider(dev, of_clk_hw_onecell_get,
					   &meson8b_hw_onecell_data);
}