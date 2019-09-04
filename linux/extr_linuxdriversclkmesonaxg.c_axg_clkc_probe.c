#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct regmap {int dummy; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct platform_device {struct device dev; } ;
struct TYPE_6__ {struct regmap* map; } ;
struct TYPE_5__ {int num; int /*<<< orphan*/ * hws; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_3__**) ; 
 scalar_t__ IS_ERR (struct regmap*) ; 
 int PTR_ERR (struct regmap*) ; 
 TYPE_3__** axg_clk_regmaps ; 
 TYPE_1__ axg_hw_onecell_data ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int devm_clk_hw_register (struct device*,int /*<<< orphan*/ ) ; 
 int devm_of_clk_add_hw_provider (struct device*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  of_clk_hw_onecell_get ; 
 int /*<<< orphan*/  of_get_parent (int /*<<< orphan*/ ) ; 
 struct regmap* syscon_node_to_regmap (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int axg_clkc_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct regmap *map;
	int ret, i;

	/* Get the hhi system controller node if available */
	map = syscon_node_to_regmap(of_get_parent(dev->of_node));
	if (IS_ERR(map)) {
		dev_err(dev, "failed to get HHI regmap\n");
		return PTR_ERR(map);
	}

	/* Populate regmap for the regmap backed clocks */
	for (i = 0; i < ARRAY_SIZE(axg_clk_regmaps); i++)
		axg_clk_regmaps[i]->map = map;

	for (i = 0; i < axg_hw_onecell_data.num; i++) {
		/* array might be sparse */
		if (!axg_hw_onecell_data.hws[i])
			continue;

		ret = devm_clk_hw_register(dev, axg_hw_onecell_data.hws[i]);
		if (ret) {
			dev_err(dev, "Clock registration failed\n");
			return ret;
		}
	}

	return devm_of_clk_add_hw_provider(dev, of_clk_hw_onecell_get,
					   &axg_hw_onecell_data);
}