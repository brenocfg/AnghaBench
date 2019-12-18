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
typedef  int u16 ;
struct pci_dev {int dummy; } ;
struct net_device {int /*<<< orphan*/  features; } ;
struct atl1e_hw {int phy_configured; scalar_t__ preamble_len; } ;
struct atl1e_adapter {int wol; int /*<<< orphan*/  netdev; struct atl1e_hw hw; int /*<<< orphan*/  flags; } ;
typedef  int /*<<< orphan*/  pm_message_t ;

/* Variables and functions */
 int ADVERTISE_10HALF ; 
 int AT_READ_REG (struct atl1e_hw*,int /*<<< orphan*/ ) ; 
 int AT_SUSPEND_LINK_TIMEOUT ; 
 int /*<<< orphan*/  AT_WRITE_REG (struct atl1e_hw*,int /*<<< orphan*/ ,int) ; 
 int AT_WUFC_LNKC ; 
 int AT_WUFC_MAG ; 
 int BMSR_LSTATUS ; 
 int MAC_CTRL_BC_EN ; 
 int MAC_CTRL_PRMLEN_MASK ; 
 int MAC_CTRL_PRMLEN_SHIFT ; 
 int MAC_CTRL_RX_EN ; 
 int MAC_CTRL_SPEED_10_100 ; 
 int MAC_CTRL_SPEED_SHIFT ; 
 int /*<<< orphan*/  MII_ADVERTISE ; 
 int /*<<< orphan*/  MII_BMSR ; 
 int /*<<< orphan*/  MII_CTRL1000 ; 
 int /*<<< orphan*/  MII_INT_CTRL ; 
 int /*<<< orphan*/  MII_INT_STATUS ; 
 int PCIE_PHYMISC_FORCE_RCV_DET ; 
 int /*<<< orphan*/  REG_MAC_CTRL ; 
 int /*<<< orphan*/  REG_PCIE_PHYMISC ; 
 int /*<<< orphan*/  REG_WOL_CTRL ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int WOL_LINK_CHG_EN ; 
 int WOL_LINK_CHG_PME_EN ; 
 int WOL_MAGIC_EN ; 
 int WOL_MAGIC_PME_EN ; 
 int /*<<< orphan*/  __AT_RESETTING ; 
 int /*<<< orphan*/  __atl1e_vlan_mode (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  atl1e_down (struct atl1e_adapter*) ; 
 int /*<<< orphan*/  atl1e_force_ps (struct atl1e_hw*) ; 
 int /*<<< orphan*/  atl1e_free_irq (struct atl1e_adapter*) ; 
 scalar_t__ atl1e_phy_commit (struct atl1e_hw*) ; 
 int /*<<< orphan*/  atl1e_read_phy_reg (struct atl1e_hw*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ atl1e_write_phy_reg (struct atl1e_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 struct atl1e_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_device_detach (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 int /*<<< orphan*/  pci_choose_state (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_enable_wake (struct pci_dev*,int /*<<< orphan*/ ,int) ; 
 struct net_device* pci_get_drvdata (struct pci_dev*) ; 
 int pci_save_state (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_power_state (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int atl1e_suspend(struct pci_dev *pdev, pm_message_t state)
{
	struct net_device *netdev = pci_get_drvdata(pdev);
	struct atl1e_adapter *adapter = netdev_priv(netdev);
	struct atl1e_hw *hw = &adapter->hw;
	u32 ctrl = 0;
	u32 mac_ctrl_data = 0;
	u32 wol_ctrl_data = 0;
	u16 mii_advertise_data = 0;
	u16 mii_bmsr_data = 0;
	u16 mii_intr_status_data = 0;
	u32 wufc = adapter->wol;
	u32 i;
#ifdef CONFIG_PM
	int retval = 0;
#endif

	if (netif_running(netdev)) {
		WARN_ON(test_bit(__AT_RESETTING, &adapter->flags));
		atl1e_down(adapter);
	}
	netif_device_detach(netdev);

#ifdef CONFIG_PM
	retval = pci_save_state(pdev);
	if (retval)
		return retval;
#endif

	if (wufc) {
		/* get link status */
		atl1e_read_phy_reg(hw, MII_BMSR, &mii_bmsr_data);
		atl1e_read_phy_reg(hw, MII_BMSR, &mii_bmsr_data);

		mii_advertise_data = ADVERTISE_10HALF;

		if ((atl1e_write_phy_reg(hw, MII_CTRL1000, 0) != 0) ||
		    (atl1e_write_phy_reg(hw,
			   MII_ADVERTISE, mii_advertise_data) != 0) ||
		    (atl1e_phy_commit(hw)) != 0) {
			netdev_dbg(adapter->netdev, "set phy register failed\n");
			goto wol_dis;
		}

		hw->phy_configured = false; /* re-init PHY when resume */

		/* turn on magic packet wol */
		if (wufc & AT_WUFC_MAG)
			wol_ctrl_data |= WOL_MAGIC_EN | WOL_MAGIC_PME_EN;

		if (wufc & AT_WUFC_LNKC) {
		/* if orignal link status is link, just wait for retrive link */
			if (mii_bmsr_data & BMSR_LSTATUS) {
				for (i = 0; i < AT_SUSPEND_LINK_TIMEOUT; i++) {
					msleep(100);
					atl1e_read_phy_reg(hw, MII_BMSR,
							&mii_bmsr_data);
					if (mii_bmsr_data & BMSR_LSTATUS)
						break;
				}

				if ((mii_bmsr_data & BMSR_LSTATUS) == 0)
					netdev_dbg(adapter->netdev,
						   "Link may change when suspend\n");
			}
			wol_ctrl_data |=  WOL_LINK_CHG_EN | WOL_LINK_CHG_PME_EN;
			/* only link up can wake up */
			if (atl1e_write_phy_reg(hw, MII_INT_CTRL, 0x400) != 0) {
				netdev_dbg(adapter->netdev,
					   "read write phy register failed\n");
				goto wol_dis;
			}
		}
		/* clear phy interrupt */
		atl1e_read_phy_reg(hw, MII_INT_STATUS, &mii_intr_status_data);
		/* Config MAC Ctrl register */
		mac_ctrl_data = MAC_CTRL_RX_EN;
		/* set to 10/100M halt duplex */
		mac_ctrl_data |= MAC_CTRL_SPEED_10_100 << MAC_CTRL_SPEED_SHIFT;
		mac_ctrl_data |= (((u32)adapter->hw.preamble_len &
				 MAC_CTRL_PRMLEN_MASK) <<
				 MAC_CTRL_PRMLEN_SHIFT);

		__atl1e_vlan_mode(netdev->features, &mac_ctrl_data);

		/* magic packet maybe Broadcast&multicast&Unicast frame */
		if (wufc & AT_WUFC_MAG)
			mac_ctrl_data |= MAC_CTRL_BC_EN;

		netdev_dbg(adapter->netdev, "suspend MAC=0x%x\n",
			   mac_ctrl_data);

		AT_WRITE_REG(hw, REG_WOL_CTRL, wol_ctrl_data);
		AT_WRITE_REG(hw, REG_MAC_CTRL, mac_ctrl_data);
		/* pcie patch */
		ctrl = AT_READ_REG(hw, REG_PCIE_PHYMISC);
		ctrl |= PCIE_PHYMISC_FORCE_RCV_DET;
		AT_WRITE_REG(hw, REG_PCIE_PHYMISC, ctrl);
		pci_enable_wake(pdev, pci_choose_state(pdev, state), 1);
		goto suspend_exit;
	}
wol_dis:

	/* WOL disabled */
	AT_WRITE_REG(hw, REG_WOL_CTRL, 0);

	/* pcie patch */
	ctrl = AT_READ_REG(hw, REG_PCIE_PHYMISC);
	ctrl |= PCIE_PHYMISC_FORCE_RCV_DET;
	AT_WRITE_REG(hw, REG_PCIE_PHYMISC, ctrl);

	atl1e_force_ps(hw);
	hw->phy_configured = false; /* re-init PHY when resume */

	pci_enable_wake(pdev, pci_choose_state(pdev, state), 0);

suspend_exit:

	if (netif_running(netdev))
		atl1e_free_irq(adapter);

	pci_disable_device(pdev);

	pci_set_power_state(pdev, pci_choose_state(pdev, state));

	return 0;
}