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
struct phy_device {scalar_t__ interrupts; } ;

/* Variables and functions */
 int DP83822_ANEG_COMPLETE_INT_EN ; 
 int DP83822_ANEG_ERR_INT_EN ; 
 int DP83822_DUP_MODE_CHANGE_INT_EN ; 
 int DP83822_EEE_ERROR_CHANGE_INT_EN ; 
 int DP83822_ENERGY_DET_INT_EN ; 
 int DP83822_FALSE_CARRIER_HF_INT_EN ; 
 int DP83822_JABBER_DET_INT_EN ; 
 int DP83822_LB_FIFO_INT_EN ; 
 int DP83822_LINK_QUAL_INT_EN ; 
 int DP83822_LINK_STAT_INT_EN ; 
 int DP83822_MDI_XOVER_INT_EN ; 
 int DP83822_PAGE_RX_INT_EN ; 
 int DP83822_PHYSCR_INTEN ; 
 int DP83822_PHYSCR_INT_OE ; 
 int DP83822_RX_ERR_HF_INT_EN ; 
 int DP83822_SLEEP_MODE_INT_EN ; 
 int DP83822_SPEED_CHANGED_INT_EN ; 
 int DP83822_WOL_PKT_INT_EN ; 
 int /*<<< orphan*/  MII_DP83822_MISR1 ; 
 int /*<<< orphan*/  MII_DP83822_MISR2 ; 
 int /*<<< orphan*/  MII_DP83822_PHYSCR ; 
 scalar_t__ PHY_INTERRUPT_ENABLED ; 
 int phy_read (struct phy_device*,int /*<<< orphan*/ ) ; 
 int phy_write (struct phy_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int dp83822_config_intr(struct phy_device *phydev)
{
	int misr_status;
	int physcr_status;
	int err;

	if (phydev->interrupts == PHY_INTERRUPT_ENABLED) {
		misr_status = phy_read(phydev, MII_DP83822_MISR1);
		if (misr_status < 0)
			return misr_status;

		misr_status |= (DP83822_RX_ERR_HF_INT_EN |
				DP83822_FALSE_CARRIER_HF_INT_EN |
				DP83822_ANEG_COMPLETE_INT_EN |
				DP83822_DUP_MODE_CHANGE_INT_EN |
				DP83822_SPEED_CHANGED_INT_EN |
				DP83822_LINK_STAT_INT_EN |
				DP83822_ENERGY_DET_INT_EN |
				DP83822_LINK_QUAL_INT_EN);

		err = phy_write(phydev, MII_DP83822_MISR1, misr_status);
		if (err < 0)
			return err;

		misr_status = phy_read(phydev, MII_DP83822_MISR2);
		if (misr_status < 0)
			return misr_status;

		misr_status |= (DP83822_JABBER_DET_INT_EN |
				DP83822_WOL_PKT_INT_EN |
				DP83822_SLEEP_MODE_INT_EN |
				DP83822_MDI_XOVER_INT_EN |
				DP83822_LB_FIFO_INT_EN |
				DP83822_PAGE_RX_INT_EN |
				DP83822_ANEG_ERR_INT_EN |
				DP83822_EEE_ERROR_CHANGE_INT_EN);

		err = phy_write(phydev, MII_DP83822_MISR2, misr_status);
		if (err < 0)
			return err;

		physcr_status = phy_read(phydev, MII_DP83822_PHYSCR);
		if (physcr_status < 0)
			return physcr_status;

		physcr_status |= DP83822_PHYSCR_INT_OE | DP83822_PHYSCR_INTEN;

	} else {
		err = phy_write(phydev, MII_DP83822_MISR1, 0);
		if (err < 0)
			return err;

		err = phy_write(phydev, MII_DP83822_MISR1, 0);
		if (err < 0)
			return err;

		physcr_status = phy_read(phydev, MII_DP83822_PHYSCR);
		if (physcr_status < 0)
			return physcr_status;

		physcr_status &= ~DP83822_PHYSCR_INTEN;
	}

	return phy_write(phydev, MII_DP83822_PHYSCR, physcr_status);
}