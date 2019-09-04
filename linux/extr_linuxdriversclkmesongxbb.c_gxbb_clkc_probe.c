#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct regmap {int dummy; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct platform_device {struct device dev; } ;
struct clkc_data {int regmap_clks_count; TYPE_3__* hw_onecell_data; TYPE_1__** regmap_clks; } ;
struct TYPE_7__ {int num; int /*<<< orphan*/ * hws; } ;
struct TYPE_6__ {struct regmap* map; } ;
struct TYPE_5__ {struct regmap* map; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_2__**) ; 
 int EINVAL ; 
 scalar_t__ IS_ERR (struct regmap*) ; 
 int PTR_ERR (struct regmap*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int devm_clk_hw_register (struct device*,int /*<<< orphan*/ ) ; 
 int devm_of_clk_add_hw_provider (struct device*,int /*<<< orphan*/ ,TYPE_3__*) ; 
 TYPE_2__** gx_clk_regmaps ; 
 int /*<<< orphan*/  of_clk_hw_onecell_get ; 
 struct clkc_data* of_device_get_match_data (struct device*) ; 
 int /*<<< orphan*/  of_get_parent (int /*<<< orphan*/ ) ; 
 struct regmap* syscon_node_to_regmap (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gxbb_clkc_probe(struct platform_device *pdev)
{
	const struct clkc_data *clkc_data;
	struct regmap *map;
	int ret, i;
	struct device *dev = &pdev->dev;

	clkc_data = of_device_get_match_data(dev);
	if (!clkc_data)
		return -EINVAL;

	/* Get the hhi system controller node if available */
	map = syscon_node_to_regmap(of_get_parent(dev->of_node));
	if (IS_ERR(map)) {
		dev_err(dev, "failed to get HHI regmap\n");
		return PTR_ERR(map);
	}

	/* Populate regmap for the common regmap backed clocks */
	for (i = 0; i < ARRAY_SIZE(gx_clk_regmaps); i++)
		gx_clk_regmaps[i]->map = map;

	/* Populate regmap for soc specific clocks */
	for (i = 0; i < clkc_data->regmap_clks_count; i++)
		clkc_data->regmap_clks[i]->map = map;

	/* Register all clks */
	for (i = 0; i < clkc_data->hw_onecell_data->num; i++) {
		/* array might be sparse */
		if (!clkc_data->hw_onecell_data->hws[i])
			continue;

		ret = devm_clk_hw_register(dev,
					   clkc_data->hw_onecell_data->hws[i]);
		if (ret) {
			dev_err(dev, "Clock registration failed\n");
			return ret;
		}
	}

	return devm_of_clk_add_hw_provider(dev, of_clk_hw_onecell_get,
					   clkc_data->hw_onecell_data);
}