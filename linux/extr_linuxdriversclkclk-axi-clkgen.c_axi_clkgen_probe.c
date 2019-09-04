#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct resource {int dummy; } ;
struct TYPE_13__ {TYPE_1__* of_node; } ;
struct platform_device {TYPE_7__ dev; } ;
struct of_device_id {int dummy; } ;
struct clk_init_data {int num_parents; char const* name; int flags; char const** parent_names; int /*<<< orphan*/ * ops; } ;
struct TYPE_12__ {struct clk_init_data* init; } ;
struct axi_clkgen {TYPE_6__ clk_hw; int /*<<< orphan*/  base; } ;
struct TYPE_11__ {char* name; } ;

/* Variables and functions */
 int CLK_SET_PARENT_GATE ; 
 int CLK_SET_RATE_GATE ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  axi_clkgen_ids ; 
 int /*<<< orphan*/  axi_clkgen_mmcm_enable (struct axi_clkgen*,int) ; 
 int /*<<< orphan*/  axi_clkgen_ops ; 
 int devm_clk_hw_register (TYPE_7__*,TYPE_6__*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (TYPE_7__*,struct resource*) ; 
 struct axi_clkgen* devm_kzalloc (TYPE_7__*,int,int /*<<< orphan*/ ) ; 
 int of_clk_add_hw_provider (TYPE_1__*,int /*<<< orphan*/ ,TYPE_6__*) ; 
 int of_clk_get_parent_count (TYPE_1__*) ; 
 char* of_clk_get_parent_name (TYPE_1__*,unsigned int) ; 
 int /*<<< orphan*/  of_clk_hw_simple_get ; 
 struct of_device_id* of_match_node (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  of_property_read_string (TYPE_1__*,char*,char const**) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int axi_clkgen_probe(struct platform_device *pdev)
{
	const struct of_device_id *id;
	struct axi_clkgen *axi_clkgen;
	struct clk_init_data init;
	const char *parent_names[2];
	const char *clk_name;
	struct resource *mem;
	unsigned int i;
	int ret;

	if (!pdev->dev.of_node)
		return -ENODEV;

	id = of_match_node(axi_clkgen_ids, pdev->dev.of_node);
	if (!id)
		return -ENODEV;

	axi_clkgen = devm_kzalloc(&pdev->dev, sizeof(*axi_clkgen), GFP_KERNEL);
	if (!axi_clkgen)
		return -ENOMEM;

	mem = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	axi_clkgen->base = devm_ioremap_resource(&pdev->dev, mem);
	if (IS_ERR(axi_clkgen->base))
		return PTR_ERR(axi_clkgen->base);

	init.num_parents = of_clk_get_parent_count(pdev->dev.of_node);
	if (init.num_parents < 1 || init.num_parents > 2)
		return -EINVAL;

	for (i = 0; i < init.num_parents; i++) {
		parent_names[i] = of_clk_get_parent_name(pdev->dev.of_node, i);
		if (!parent_names[i])
			return -EINVAL;
	}

	clk_name = pdev->dev.of_node->name;
	of_property_read_string(pdev->dev.of_node, "clock-output-names",
		&clk_name);

	init.name = clk_name;
	init.ops = &axi_clkgen_ops;
	init.flags = CLK_SET_RATE_GATE | CLK_SET_PARENT_GATE;
	init.parent_names = parent_names;

	axi_clkgen_mmcm_enable(axi_clkgen, false);

	axi_clkgen->clk_hw.init = &init;
	ret = devm_clk_hw_register(&pdev->dev, &axi_clkgen->clk_hw);
	if (ret)
		return ret;

	return of_clk_add_hw_provider(pdev->dev.of_node, of_clk_hw_simple_get,
				      &axi_clkgen->clk_hw);
}