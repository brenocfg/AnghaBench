#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct regmap {int dummy; } ;
struct TYPE_7__ {struct device_node* of_node; } ;
struct platform_device {TYPE_2__ dev; } ;
struct oxnas_stdclk_data {int ngates; TYPE_3__* onecell_data; TYPE_1__** gates; } ;
struct of_device_id {struct oxnas_stdclk_data* data; } ;
struct device_node {int dummy; } ;
struct TYPE_8__ {int num; int /*<<< orphan*/ * hws; } ;
struct TYPE_6__ {struct regmap* regmap; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ IS_ERR (struct regmap*) ; 
 int PTR_ERR (struct regmap*) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*) ; 
 int devm_clk_hw_register (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int of_clk_add_hw_provider (struct device_node*,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  of_clk_hw_onecell_get ; 
 int /*<<< orphan*/  of_get_parent (struct device_node*) ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  oxnas_stdclk_dt_ids ; 
 struct regmap* syscon_node_to_regmap (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int oxnas_stdclk_probe(struct platform_device *pdev)
{
	struct device_node *np = pdev->dev.of_node;
	const struct oxnas_stdclk_data *data;
	const struct of_device_id *id;
	struct regmap *regmap;
	int ret;
	int i;

	id = of_match_device(oxnas_stdclk_dt_ids, &pdev->dev);
	if (!id)
		return -ENODEV;
	data = id->data;

	regmap = syscon_node_to_regmap(of_get_parent(np));
	if (IS_ERR(regmap)) {
		dev_err(&pdev->dev, "failed to have parent regmap\n");
		return PTR_ERR(regmap);
	}

	for (i = 0 ; i < data->ngates ; ++i)
		data->gates[i]->regmap = regmap;

	for (i = 0; i < data->onecell_data->num; i++) {
		if (!data->onecell_data->hws[i])
			continue;

		ret = devm_clk_hw_register(&pdev->dev,
					   data->onecell_data->hws[i]);
		if (ret)
			return ret;
	}

	return of_clk_add_hw_provider(np, of_clk_hw_onecell_get,
				      data->onecell_data);
}