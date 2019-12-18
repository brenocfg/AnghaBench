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
struct ti_pipe3 {scalar_t__ mode; int /*<<< orphan*/  pll_ctrl_base; struct device* dev; } ;
struct resource {int dummy; } ;
struct platform_device {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ PIPE3_MODE_PCIE ; 
 int PTR_ERR_OR_ZERO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_ioremap_resource (struct device*,struct resource*) ; 
 struct resource* platform_get_resource_byname (struct platform_device*,int /*<<< orphan*/ ,char*) ; 
 struct platform_device* to_platform_device (struct device*) ; 

__attribute__((used)) static int ti_pipe3_get_pll_base(struct ti_pipe3 *phy)
{
	struct resource *res;
	struct device *dev = phy->dev;
	struct platform_device *pdev = to_platform_device(dev);

	if (phy->mode == PIPE3_MODE_PCIE)
		return 0;

	res = platform_get_resource_byname(pdev, IORESOURCE_MEM,
					   "pll_ctrl");
	phy->pll_ctrl_base = devm_ioremap_resource(dev, res);
	return PTR_ERR_OR_ZERO(phy->pll_ctrl_base);
}