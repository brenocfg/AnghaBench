#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_1__ dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_info (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  of_platform_populate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int of_pm_clk_add_clk (TYPE_1__*,char*) ; 
 int pm_clk_create (TYPE_1__*) ; 
 int /*<<< orphan*/  pm_clk_destroy (TYPE_1__*) ; 
 int /*<<< orphan*/  pm_runtime_enable (TYPE_1__*) ; 

__attribute__((used)) static int tegra_aconnect_probe(struct platform_device *pdev)
{
	int ret;

	if (!pdev->dev.of_node)
		return -EINVAL;

	ret = pm_clk_create(&pdev->dev);
	if (ret)
		return ret;

	ret = of_pm_clk_add_clk(&pdev->dev, "ape");
	if (ret)
		goto clk_destroy;

	ret = of_pm_clk_add_clk(&pdev->dev, "apb2ape");
	if (ret)
		goto clk_destroy;

	pm_runtime_enable(&pdev->dev);

	of_platform_populate(pdev->dev.of_node, NULL, NULL, &pdev->dev);

	dev_info(&pdev->dev, "Tegra ACONNECT bus registered\n");

	return 0;

clk_destroy:
	pm_clk_destroy(&pdev->dev);

	return ret;
}