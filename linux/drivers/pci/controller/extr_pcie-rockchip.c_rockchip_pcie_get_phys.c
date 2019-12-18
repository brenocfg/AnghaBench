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
typedef  size_t u32 ;
struct rockchip_pcie {int legacy_phy; struct phy** phys; struct device* dev; } ;
struct phy {int dummy; } ;
struct device {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct phy*) ; 
 size_t MAX_LANE_NUM ; 
 int PTR_ERR (struct phy*) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,size_t,int) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*) ; 
 struct phy* devm_of_phy_get (struct device*,int /*<<< orphan*/ ,char*) ; 
 struct phy* devm_phy_get (struct device*,char*) ; 
 char* kasprintf (int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  kfree (char*) ; 

int rockchip_pcie_get_phys(struct rockchip_pcie *rockchip)
{
	struct device *dev = rockchip->dev;
	struct phy *phy;
	char *name;
	u32 i;

	phy = devm_phy_get(dev, "pcie-phy");
	if (!IS_ERR(phy)) {
		rockchip->legacy_phy = true;
		rockchip->phys[0] = phy;
		dev_warn(dev, "legacy phy model is deprecated!\n");
		return 0;
	}

	if (PTR_ERR(phy) == -EPROBE_DEFER)
		return PTR_ERR(phy);

	dev_dbg(dev, "missing legacy phy; search for per-lane PHY\n");

	for (i = 0; i < MAX_LANE_NUM; i++) {
		name = kasprintf(GFP_KERNEL, "pcie-phy-%u", i);
		if (!name)
			return -ENOMEM;

		phy = devm_of_phy_get(dev, dev->of_node, name);
		kfree(name);

		if (IS_ERR(phy)) {
			if (PTR_ERR(phy) != -EPROBE_DEFER)
				dev_err(dev, "missing phy for lane %d: %ld\n",
					i, PTR_ERR(phy));
			return PTR_ERR(phy);
		}

		rockchip->phys[i] = phy;
	}

	return 0;
}