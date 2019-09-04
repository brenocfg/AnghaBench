#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct resource {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  of_node; int /*<<< orphan*/ * funcs; struct rcar_lvds* driver_private; } ;
struct rcar_lvds {int enabled; TYPE_2__ bridge; int /*<<< orphan*/  clock; int /*<<< orphan*/  mmio; int /*<<< orphan*/  info; TYPE_1__* dev; } ;
struct TYPE_7__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_1__ dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  devm_clk_get (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_ioremap_resource (TYPE_1__*,struct resource*) ; 
 struct rcar_lvds* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_bridge_add (TYPE_2__*) ; 
 int /*<<< orphan*/  of_device_get_match_data (TYPE_1__*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct rcar_lvds*) ; 
 int /*<<< orphan*/  rcar_lvds_bridge_ops ; 
 int rcar_lvds_parse_dt (struct rcar_lvds*) ; 

__attribute__((used)) static int rcar_lvds_probe(struct platform_device *pdev)
{
	struct rcar_lvds *lvds;
	struct resource *mem;
	int ret;

	lvds = devm_kzalloc(&pdev->dev, sizeof(*lvds), GFP_KERNEL);
	if (lvds == NULL)
		return -ENOMEM;

	platform_set_drvdata(pdev, lvds);

	lvds->dev = &pdev->dev;
	lvds->info = of_device_get_match_data(&pdev->dev);
	lvds->enabled = false;

	ret = rcar_lvds_parse_dt(lvds);
	if (ret < 0)
		return ret;

	lvds->bridge.driver_private = lvds;
	lvds->bridge.funcs = &rcar_lvds_bridge_ops;
	lvds->bridge.of_node = pdev->dev.of_node;

	mem = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	lvds->mmio = devm_ioremap_resource(&pdev->dev, mem);
	if (IS_ERR(lvds->mmio))
		return PTR_ERR(lvds->mmio);

	lvds->clock = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(lvds->clock)) {
		dev_err(&pdev->dev, "failed to get clock\n");
		return PTR_ERR(lvds->clock);
	}

	drm_bridge_add(&lvds->bridge);

	return 0;
}