#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct xsphy_instance {int type; int /*<<< orphan*/  ref_clk; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct phy {TYPE_1__ dev; } ;
struct mtk_xsphy {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
#define  PHY_TYPE_USB2 129 
#define  PHY_TYPE_USB3 128 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct mtk_xsphy* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 struct xsphy_instance* phy_get_drvdata (struct phy*) ; 
 int /*<<< orphan*/  u2_phy_instance_init (struct mtk_xsphy*,struct xsphy_instance*) ; 
 int /*<<< orphan*/  u2_phy_props_set (struct mtk_xsphy*,struct xsphy_instance*) ; 
 int /*<<< orphan*/  u3_phy_props_set (struct mtk_xsphy*,struct xsphy_instance*) ; 

__attribute__((used)) static int mtk_phy_init(struct phy *phy)
{
	struct xsphy_instance *inst = phy_get_drvdata(phy);
	struct mtk_xsphy *xsphy = dev_get_drvdata(phy->dev.parent);
	int ret;

	ret = clk_prepare_enable(inst->ref_clk);
	if (ret) {
		dev_err(xsphy->dev, "failed to enable ref_clk\n");
		return ret;
	}

	switch (inst->type) {
	case PHY_TYPE_USB2:
		u2_phy_instance_init(xsphy, inst);
		u2_phy_props_set(xsphy, inst);
		break;
	case PHY_TYPE_USB3:
		u3_phy_props_set(xsphy, inst);
		break;
	default:
		dev_err(xsphy->dev, "incompatible phy type\n");
		clk_disable_unprepare(inst->ref_clk);
		return -EINVAL;
	}

	return 0;
}