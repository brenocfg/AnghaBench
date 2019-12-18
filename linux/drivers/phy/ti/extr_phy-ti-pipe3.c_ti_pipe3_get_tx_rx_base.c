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
struct ti_pipe3 {void* phy_tx; void* phy_rx; struct device* dev; } ;
struct resource {int dummy; } ;
struct platform_device {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int PTR_ERR_OR_ZERO (void*) ; 
 void* devm_ioremap_resource (struct device*,struct resource*) ; 
 struct resource* platform_get_resource_byname (struct platform_device*,int /*<<< orphan*/ ,char*) ; 
 struct platform_device* to_platform_device (struct device*) ; 

__attribute__((used)) static int ti_pipe3_get_tx_rx_base(struct ti_pipe3 *phy)
{
	struct resource *res;
	struct device *dev = phy->dev;
	struct platform_device *pdev = to_platform_device(dev);

	res = platform_get_resource_byname(pdev, IORESOURCE_MEM,
					   "phy_rx");
	phy->phy_rx = devm_ioremap_resource(dev, res);
	if (IS_ERR(phy->phy_rx))
		return PTR_ERR(phy->phy_rx);

	res = platform_get_resource_byname(pdev, IORESOURCE_MEM,
					   "phy_tx");
	phy->phy_tx = devm_ioremap_resource(dev, res);

	return PTR_ERR_OR_ZERO(phy->phy_tx);
}