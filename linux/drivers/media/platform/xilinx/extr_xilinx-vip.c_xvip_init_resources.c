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
struct xvip_device {int /*<<< orphan*/  clk; int /*<<< orphan*/  dev; int /*<<< orphan*/  iomem; } ;
struct resource {int dummy; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_clk_get (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_ioremap_resource (int /*<<< orphan*/ ,struct resource*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct platform_device* to_platform_device (int /*<<< orphan*/ ) ; 

int xvip_init_resources(struct xvip_device *xvip)
{
	struct platform_device *pdev = to_platform_device(xvip->dev);
	struct resource *res;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	xvip->iomem = devm_ioremap_resource(xvip->dev, res);
	if (IS_ERR(xvip->iomem))
		return PTR_ERR(xvip->iomem);

	xvip->clk = devm_clk_get(xvip->dev, NULL);
	if (IS_ERR(xvip->clk))
		return PTR_ERR(xvip->clk);

	clk_prepare_enable(xvip->clk);
	return 0;
}