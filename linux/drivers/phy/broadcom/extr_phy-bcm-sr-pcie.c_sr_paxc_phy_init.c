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
typedef  int u32 ;
struct sr_pcie_phy_core {int /*<<< orphan*/  dev; int /*<<< orphan*/  mhb; } ;
struct sr_pcie_phy {unsigned int index; struct sr_pcie_phy_core* core; } ;
struct phy {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  MHB_MEM_PW_PAXC_OFFSET ; 
 int MHB_PWR_STATUS_MASK ; 
 unsigned int SR_PAXC_PHY_IDX ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct sr_pcie_phy* phy_get_drvdata (struct phy*) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int sr_paxc_phy_init(struct phy *p)
{
	struct sr_pcie_phy *phy = phy_get_drvdata(p);
	struct sr_pcie_phy_core *core = phy->core;
	unsigned int core_idx = phy->index;
	u32 val;

	if (core_idx != SR_PAXC_PHY_IDX)
		return -EINVAL;

	regmap_read(core->mhb, MHB_MEM_PW_PAXC_OFFSET, &val);
	if ((val & MHB_PWR_STATUS_MASK) != MHB_PWR_STATUS_MASK) {
		dev_err(core->dev, "PAXC is not powered up\n");
		return -ENODEV;
	}

	return 0;
}