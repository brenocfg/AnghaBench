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
struct resource {int dummy; } ;
struct device {TYPE_1__* of_node; } ;
struct platform_device {struct device dev; } ;
struct clk_init_data {char const** parent_names; int num_parents; int /*<<< orphan*/  name; int /*<<< orphan*/ * ops; } ;
struct TYPE_6__ {struct clk_init_data* init; } ;
struct axs10x_pll_clk {TYPE_3__ hw; int /*<<< orphan*/  pll_cfg; struct device* dev; void* lock; void* base; } ;
struct TYPE_5__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  axs10x_pll_ops ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int devm_clk_hw_register (struct device*,TYPE_3__*) ; 
 void* devm_ioremap_resource (struct device*,struct resource*) ; 
 struct axs10x_pll_clk* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int of_clk_add_hw_provider (TYPE_1__*,int /*<<< orphan*/ ,TYPE_3__*) ; 
 char* of_clk_get_parent_name (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_clk_hw_simple_get ; 
 int /*<<< orphan*/  of_device_get_match_data (struct device*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int axs10x_pll_clk_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	const char *parent_name;
	struct axs10x_pll_clk *pll_clk;
	struct resource *mem;
	struct clk_init_data init = { };
	int ret;

	pll_clk = devm_kzalloc(dev, sizeof(*pll_clk), GFP_KERNEL);
	if (!pll_clk)
		return -ENOMEM;

	mem = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	pll_clk->base = devm_ioremap_resource(dev, mem);
	if (IS_ERR(pll_clk->base))
		return PTR_ERR(pll_clk->base);

	mem = platform_get_resource(pdev, IORESOURCE_MEM, 1);
	pll_clk->lock = devm_ioremap_resource(dev, mem);
	if (IS_ERR(pll_clk->lock))
		return PTR_ERR(pll_clk->lock);

	init.name = dev->of_node->name;
	init.ops = &axs10x_pll_ops;
	parent_name = of_clk_get_parent_name(dev->of_node, 0);
	init.parent_names = &parent_name;
	init.num_parents = 1;
	pll_clk->hw.init = &init;
	pll_clk->dev = dev;
	pll_clk->pll_cfg = of_device_get_match_data(dev);

	if (!pll_clk->pll_cfg) {
		dev_err(dev, "No OF match data provided\n");
		return -EINVAL;
	}

	ret = devm_clk_hw_register(dev, &pll_clk->hw);
	if (ret) {
		dev_err(dev, "failed to register %s clock\n", init.name);
		return ret;
	}

	return of_clk_add_hw_provider(dev->of_node, of_clk_hw_simple_get,
			&pll_clk->hw);
}