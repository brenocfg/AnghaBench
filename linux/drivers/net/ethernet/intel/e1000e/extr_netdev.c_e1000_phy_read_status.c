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
struct e1000_phy_regs {int bmcr; int bmsr; int advertise; int lpa; int expansion; int ctrl1000; int stat1000; int estatus; } ;
struct TYPE_6__ {scalar_t__ media_type; } ;
struct e1000_hw {TYPE_3__ phy; } ;
struct e1000_adapter {struct e1000_hw hw; TYPE_2__* pdev; struct e1000_phy_regs phy_regs; } ;
struct TYPE_4__ {int /*<<< orphan*/  parent; } ;
struct TYPE_5__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int ADVERTISE_1000FULL ; 
 int ADVERTISE_ALL ; 
 int ADVERTISE_CSMA ; 
 int ADVERTISE_PAUSE_ASYM ; 
 int ADVERTISE_PAUSE_CAP ; 
 int BMCR_ANENABLE ; 
 int BMCR_FULLDPLX ; 
 int BMCR_SPEED1000 ; 
 int BMSR_100FULL ; 
 int BMSR_100HALF ; 
 int BMSR_10FULL ; 
 int BMSR_10HALF ; 
 int BMSR_ANEGCAPABLE ; 
 int BMSR_ERCAP ; 
 int BMSR_ESTATEN ; 
 int E1000_STATUS_LU ; 
 int ESTATUS_1000_TFULL ; 
 int ESTATUS_1000_THALF ; 
 int EXPANSION_ENABLENPAGE ; 
 int /*<<< orphan*/  MII_ADVERTISE ; 
 int /*<<< orphan*/  MII_BMCR ; 
 int /*<<< orphan*/  MII_BMSR ; 
 int /*<<< orphan*/  MII_CTRL1000 ; 
 int /*<<< orphan*/  MII_ESTATUS ; 
 int /*<<< orphan*/  MII_EXPANSION ; 
 int /*<<< orphan*/  MII_LPA ; 
 int /*<<< orphan*/  MII_STAT1000 ; 
 int /*<<< orphan*/  STATUS ; 
 scalar_t__ e1000_media_type_copper ; 
 int e1e_rphy (struct e1000_hw*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  e_warn (char*) ; 
 int er32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_suspended (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void e1000_phy_read_status(struct e1000_adapter *adapter)
{
	struct e1000_hw *hw = &adapter->hw;
	struct e1000_phy_regs *phy = &adapter->phy_regs;

	if (!pm_runtime_suspended((&adapter->pdev->dev)->parent) &&
	    (er32(STATUS) & E1000_STATUS_LU) &&
	    (adapter->hw.phy.media_type == e1000_media_type_copper)) {
		int ret_val;

		ret_val = e1e_rphy(hw, MII_BMCR, &phy->bmcr);
		ret_val |= e1e_rphy(hw, MII_BMSR, &phy->bmsr);
		ret_val |= e1e_rphy(hw, MII_ADVERTISE, &phy->advertise);
		ret_val |= e1e_rphy(hw, MII_LPA, &phy->lpa);
		ret_val |= e1e_rphy(hw, MII_EXPANSION, &phy->expansion);
		ret_val |= e1e_rphy(hw, MII_CTRL1000, &phy->ctrl1000);
		ret_val |= e1e_rphy(hw, MII_STAT1000, &phy->stat1000);
		ret_val |= e1e_rphy(hw, MII_ESTATUS, &phy->estatus);
		if (ret_val)
			e_warn("Error reading PHY register\n");
	} else {
		/* Do not read PHY registers if link is not up
		 * Set values to typical power-on defaults
		 */
		phy->bmcr = (BMCR_SPEED1000 | BMCR_ANENABLE | BMCR_FULLDPLX);
		phy->bmsr = (BMSR_100FULL | BMSR_100HALF | BMSR_10FULL |
			     BMSR_10HALF | BMSR_ESTATEN | BMSR_ANEGCAPABLE |
			     BMSR_ERCAP);
		phy->advertise = (ADVERTISE_PAUSE_ASYM | ADVERTISE_PAUSE_CAP |
				  ADVERTISE_ALL | ADVERTISE_CSMA);
		phy->lpa = 0;
		phy->expansion = EXPANSION_ENABLENPAGE;
		phy->ctrl1000 = ADVERTISE_1000FULL;
		phy->stat1000 = 0;
		phy->estatus = (ESTATUS_1000_TFULL | ESTATUS_1000_THALF);
	}
}