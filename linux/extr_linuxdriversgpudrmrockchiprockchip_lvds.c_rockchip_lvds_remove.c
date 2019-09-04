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
struct rockchip_lvds {int /*<<< orphan*/  pclk; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  component_del (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct rockchip_lvds* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rockchip_lvds_component_ops ; 

__attribute__((used)) static int rockchip_lvds_remove(struct platform_device *pdev)
{
	struct rockchip_lvds *lvds = dev_get_drvdata(&pdev->dev);

	component_del(&pdev->dev, &rockchip_lvds_component_ops);
	clk_unprepare(lvds->pclk);

	return 0;
}