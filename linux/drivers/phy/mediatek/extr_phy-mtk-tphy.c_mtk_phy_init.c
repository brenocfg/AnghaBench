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
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct phy {TYPE_1__ dev; } ;
struct mtk_tphy {int /*<<< orphan*/  dev; int /*<<< orphan*/  u3phya_ref; } ;
struct mtk_phy_instance {int type; int /*<<< orphan*/  ref_clk; } ;

/* Variables and functions */
 int EINVAL ; 
#define  PHY_TYPE_PCIE 131 
#define  PHY_TYPE_SATA 130 
#define  PHY_TYPE_USB2 129 
#define  PHY_TYPE_USB3 128 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct mtk_tphy* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcie_phy_instance_init (struct mtk_tphy*,struct mtk_phy_instance*) ; 
 struct mtk_phy_instance* phy_get_drvdata (struct phy*) ; 
 int /*<<< orphan*/  sata_phy_instance_init (struct mtk_tphy*,struct mtk_phy_instance*) ; 
 int /*<<< orphan*/  u2_phy_instance_init (struct mtk_tphy*,struct mtk_phy_instance*) ; 
 int /*<<< orphan*/  u2_phy_props_set (struct mtk_tphy*,struct mtk_phy_instance*) ; 
 int /*<<< orphan*/  u3_phy_instance_init (struct mtk_tphy*,struct mtk_phy_instance*) ; 

__attribute__((used)) static int mtk_phy_init(struct phy *phy)
{
	struct mtk_phy_instance *instance = phy_get_drvdata(phy);
	struct mtk_tphy *tphy = dev_get_drvdata(phy->dev.parent);
	int ret;

	ret = clk_prepare_enable(tphy->u3phya_ref);
	if (ret) {
		dev_err(tphy->dev, "failed to enable u3phya_ref\n");
		return ret;
	}

	ret = clk_prepare_enable(instance->ref_clk);
	if (ret) {
		dev_err(tphy->dev, "failed to enable ref_clk\n");
		return ret;
	}

	switch (instance->type) {
	case PHY_TYPE_USB2:
		u2_phy_instance_init(tphy, instance);
		u2_phy_props_set(tphy, instance);
		break;
	case PHY_TYPE_USB3:
		u3_phy_instance_init(tphy, instance);
		break;
	case PHY_TYPE_PCIE:
		pcie_phy_instance_init(tphy, instance);
		break;
	case PHY_TYPE_SATA:
		sata_phy_instance_init(tphy, instance);
		break;
	default:
		dev_err(tphy->dev, "incompatible PHY type\n");
		return -EINVAL;
	}

	return 0;
}