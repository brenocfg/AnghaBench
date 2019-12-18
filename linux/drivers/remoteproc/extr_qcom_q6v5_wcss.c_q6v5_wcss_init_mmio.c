#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct resource {int dummy; } ;
struct q6v5_wcss {int /*<<< orphan*/  halt_nc; int /*<<< orphan*/  halt_wcss; int /*<<< orphan*/  halt_q6; void* halt_map; void* rmb_base; void* reg_base; } ;
struct TYPE_3__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct of_phandle_args {int /*<<< orphan*/ * args; int /*<<< orphan*/  np; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 void* devm_ioremap_resource (TYPE_1__*,struct resource*) ; 
 int /*<<< orphan*/  of_node_put (int /*<<< orphan*/ ) ; 
 int of_parse_phandle_with_fixed_args (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,struct of_phandle_args*) ; 
 struct resource* platform_get_resource_byname (struct platform_device*,int /*<<< orphan*/ ,char*) ; 
 void* syscon_node_to_regmap (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int q6v5_wcss_init_mmio(struct q6v5_wcss *wcss,
			       struct platform_device *pdev)
{
	struct of_phandle_args args;
	struct resource *res;
	int ret;

	res = platform_get_resource_byname(pdev, IORESOURCE_MEM, "qdsp6");
	wcss->reg_base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(wcss->reg_base))
		return PTR_ERR(wcss->reg_base);

	res = platform_get_resource_byname(pdev, IORESOURCE_MEM, "rmb");
	wcss->rmb_base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(wcss->rmb_base))
		return PTR_ERR(wcss->rmb_base);

	ret = of_parse_phandle_with_fixed_args(pdev->dev.of_node,
					       "qcom,halt-regs", 3, 0, &args);
	if (ret < 0) {
		dev_err(&pdev->dev, "failed to parse qcom,halt-regs\n");
		return -EINVAL;
	}

	wcss->halt_map = syscon_node_to_regmap(args.np);
	of_node_put(args.np);
	if (IS_ERR(wcss->halt_map))
		return PTR_ERR(wcss->halt_map);

	wcss->halt_q6 = args.args[0];
	wcss->halt_wcss = args.args[1];
	wcss->halt_nc = args.args[2];

	return 0;
}