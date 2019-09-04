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
struct device {int /*<<< orphan*/  of_node; } ;
struct platform_device {struct device dev; } ;
struct clk_init_data {char* name; scalar_t__ num_parents; int /*<<< orphan*/ * parent_names; int /*<<< orphan*/  flags; int /*<<< orphan*/ * ops; } ;
struct TYPE_2__ {struct clk_init_data* init; } ;
struct clk_allo_hw {TYPE_1__ hw; scalar_t__ mode; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLK_IS_BASIC ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IS_ERR (struct clk*) ; 
 int PTR_ERR (struct clk*) ; 
 int /*<<< orphan*/  clk_allo_dac_rate_ops ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct clk* devm_clk_register (struct device*,TYPE_1__*) ; 
 int /*<<< orphan*/  kfree (struct clk_allo_hw*) ; 
 struct clk_allo_hw* kzalloc (int,int /*<<< orphan*/ ) ; 
 int of_clk_add_provider (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct clk*) ; 
 int /*<<< orphan*/  of_clk_src_simple_get ; 

__attribute__((used)) static int clk_allo_dac_probe(struct platform_device *pdev)
{
	int ret;
	struct clk_allo_hw *proclk;
	struct clk *clk;
	struct device *dev;
	struct clk_init_data init;

	dev = &pdev->dev;

	proclk = kzalloc(sizeof(struct clk_allo_hw), GFP_KERNEL);
	if (!proclk)
		return -ENOMEM;

	init.name = "clk-allo-dac";
	init.ops = &clk_allo_dac_rate_ops;
	init.flags = CLK_IS_BASIC;
	init.parent_names = NULL;
	init.num_parents = 0;

	proclk->mode = 0;
	proclk->hw.init = &init;

	clk = devm_clk_register(dev, &proclk->hw);
	if (!IS_ERR(clk)) {
		ret = of_clk_add_provider(dev->of_node, of_clk_src_simple_get,
			clk);
	} else {
		dev_err(dev, "Fail to register clock driver\n");
		kfree(proclk);
		ret = PTR_ERR(clk);
	}
	return ret;
}