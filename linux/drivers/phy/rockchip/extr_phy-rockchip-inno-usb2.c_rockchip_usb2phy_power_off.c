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
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct rockchip_usb2phy_port {int suspended; TYPE_1__* port_cfg; TYPE_3__* phy; } ;
struct rockchip_usb2phy {int /*<<< orphan*/  clk480m; } ;
struct regmap {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  parent; } ;
struct phy {TYPE_2__ dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  phy_sus; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 struct rockchip_usb2phy* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 struct regmap* get_reg_base (struct rockchip_usb2phy*) ; 
 struct rockchip_usb2phy_port* phy_get_drvdata (struct phy*) ; 
 int property_enable (struct regmap*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int rockchip_usb2phy_power_off(struct phy *phy)
{
	struct rockchip_usb2phy_port *rport = phy_get_drvdata(phy);
	struct rockchip_usb2phy *rphy = dev_get_drvdata(phy->dev.parent);
	struct regmap *base = get_reg_base(rphy);
	int ret;

	dev_dbg(&rport->phy->dev, "port power off\n");

	if (rport->suspended)
		return 0;

	ret = property_enable(base, &rport->port_cfg->phy_sus, true);
	if (ret)
		return ret;

	rport->suspended = true;
	clk_disable_unprepare(rphy->clk480m);

	return 0;
}