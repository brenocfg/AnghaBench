#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int u16 ;
struct pci_dev {TYPE_6__* bus; } ;
struct net_device {int dummy; } ;
struct TYPE_10__ {int (* acquire ) (struct e1000_hw*) ;int /*<<< orphan*/  (* release ) (struct e1000_hw*) ;} ;
struct TYPE_11__ {scalar_t__ media_type; scalar_t__ type; TYPE_4__ ops; } ;
struct TYPE_8__ {int eee_lp_ability; } ;
struct TYPE_9__ {TYPE_2__ ich8lan; } ;
struct TYPE_7__ {scalar_t__ type; } ;
struct e1000_hw {TYPE_5__ phy; TYPE_3__ dev_spec; TYPE_1__ mac; } ;
struct e1000_adapter {int wol; int flags2; int flags; int eee_advert; struct e1000_hw hw; } ;
struct TYPE_12__ {struct pci_dev* self; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTRL ; 
 int /*<<< orphan*/  CTRL_EXT ; 
 int E1000_CTRL_ADVD3WUC ; 
 int E1000_CTRL_EN_PHY_PWR_MGMT ; 
 int E1000_CTRL_EXT_SDP3_DATA ; 
 int E1000_RCTL_MPE ; 
 int E1000_STATUS_LU ; 
 int E1000_WUC_PME_EN ; 
 int E1000_WUFC_BC ; 
 int E1000_WUFC_EX ; 
 int E1000_WUFC_LNKC ; 
 int E1000_WUFC_MC ; 
 int FLAG2_HAS_PHY_WAKEUP ; 
 int FLAG_IS_ICH ; 
 int FLAG_IS_QUAD_PORT ; 
 int I82579_EEE_1000_SUPPORTED ; 
 int I82579_EEE_100_SUPPORTED ; 
 int /*<<< orphan*/  I82579_LPI_CTRL ; 
 int I82579_LPI_CTRL_1000_ENABLE ; 
 int I82579_LPI_CTRL_100_ENABLE ; 
 int /*<<< orphan*/  PCI_EXP_DEVCTL ; 
 int PCI_EXP_DEVCTL_CERE ; 
 int /*<<< orphan*/  RCTL ; 
 int /*<<< orphan*/  STATUS ; 
 int /*<<< orphan*/  WUC ; 
 int /*<<< orphan*/  WUFC ; 
 int e1000_enable_ulp_lpt_lp (struct e1000_hw*,int) ; 
 int e1000_init_phy_wakeup (struct e1000_adapter*,int) ; 
 scalar_t__ e1000_media_type_fiber ; 
 scalar_t__ e1000_media_type_internal_serdes ; 
 scalar_t__ e1000_pch_lpt ; 
 scalar_t__ e1000_phy_i217 ; 
 scalar_t__ e1000_phy_igp_3 ; 
 int /*<<< orphan*/  e1000_power_down_phy (struct e1000_adapter*) ; 
 int /*<<< orphan*/  e1000_setup_rctl (struct e1000_adapter*) ; 
 int /*<<< orphan*/  e1000_suspend_workarounds_ich8lan (struct e1000_hw*) ; 
 int /*<<< orphan*/  e1000e_igp3_phy_powerdown_workaround_ich8lan (struct e1000_hw*) ; 
 int /*<<< orphan*/  e1000e_power_up_phy (struct e1000_adapter*) ; 
 int /*<<< orphan*/  e1000e_release_hw_control (struct e1000_adapter*) ; 
 int /*<<< orphan*/  e1000e_set_rx_mode (struct net_device*) ; 
 int e1e_rphy_locked (struct e1000_hw*,int /*<<< orphan*/ ,int*) ; 
 int e1e_wphy_locked (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 
 int er32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ew32 (int /*<<< orphan*/ ,int) ; 
 struct e1000_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pci_clear_master (struct pci_dev*) ; 
 struct net_device* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_prepare_to_sleep (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_save_state (struct pci_dev*) ; 
 int /*<<< orphan*/  pcie_capability_read_word (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pcie_capability_write_word (struct pci_dev*,int /*<<< orphan*/ ,int) ; 
 int stub1 (struct e1000_hw*) ; 
 int /*<<< orphan*/  stub2 (struct e1000_hw*) ; 

__attribute__((used)) static int __e1000_shutdown(struct pci_dev *pdev, bool runtime)
{
	struct net_device *netdev = pci_get_drvdata(pdev);
	struct e1000_adapter *adapter = netdev_priv(netdev);
	struct e1000_hw *hw = &adapter->hw;
	u32 ctrl, ctrl_ext, rctl, status;
	/* Runtime suspend should only enable wakeup for link changes */
	u32 wufc = runtime ? E1000_WUFC_LNKC : adapter->wol;
	int retval = 0;

	status = er32(STATUS);
	if (status & E1000_STATUS_LU)
		wufc &= ~E1000_WUFC_LNKC;

	if (wufc) {
		e1000_setup_rctl(adapter);
		e1000e_set_rx_mode(netdev);

		/* turn on all-multi mode if wake on multicast is enabled */
		if (wufc & E1000_WUFC_MC) {
			rctl = er32(RCTL);
			rctl |= E1000_RCTL_MPE;
			ew32(RCTL, rctl);
		}

		ctrl = er32(CTRL);
		ctrl |= E1000_CTRL_ADVD3WUC;
		if (!(adapter->flags2 & FLAG2_HAS_PHY_WAKEUP))
			ctrl |= E1000_CTRL_EN_PHY_PWR_MGMT;
		ew32(CTRL, ctrl);

		if (adapter->hw.phy.media_type == e1000_media_type_fiber ||
		    adapter->hw.phy.media_type ==
		    e1000_media_type_internal_serdes) {
			/* keep the laser running in D3 */
			ctrl_ext = er32(CTRL_EXT);
			ctrl_ext |= E1000_CTRL_EXT_SDP3_DATA;
			ew32(CTRL_EXT, ctrl_ext);
		}

		if (!runtime)
			e1000e_power_up_phy(adapter);

		if (adapter->flags & FLAG_IS_ICH)
			e1000_suspend_workarounds_ich8lan(&adapter->hw);

		if (adapter->flags2 & FLAG2_HAS_PHY_WAKEUP) {
			/* enable wakeup by the PHY */
			retval = e1000_init_phy_wakeup(adapter, wufc);
			if (retval)
				return retval;
		} else {
			/* enable wakeup by the MAC */
			ew32(WUFC, wufc);
			ew32(WUC, E1000_WUC_PME_EN);
		}
	} else {
		ew32(WUC, 0);
		ew32(WUFC, 0);

		e1000_power_down_phy(adapter);
	}

	if (adapter->hw.phy.type == e1000_phy_igp_3) {
		e1000e_igp3_phy_powerdown_workaround_ich8lan(&adapter->hw);
	} else if (hw->mac.type >= e1000_pch_lpt) {
		if (!(wufc & (E1000_WUFC_EX | E1000_WUFC_MC | E1000_WUFC_BC)))
			/* ULP does not support wake from unicast, multicast
			 * or broadcast.
			 */
			retval = e1000_enable_ulp_lpt_lp(hw, !runtime);

		if (retval)
			return retval;
	}

	/* Ensure that the appropriate bits are set in LPI_CTRL
	 * for EEE in Sx
	 */
	if ((hw->phy.type >= e1000_phy_i217) &&
	    adapter->eee_advert && hw->dev_spec.ich8lan.eee_lp_ability) {
		u16 lpi_ctrl = 0;

		retval = hw->phy.ops.acquire(hw);
		if (!retval) {
			retval = e1e_rphy_locked(hw, I82579_LPI_CTRL,
						 &lpi_ctrl);
			if (!retval) {
				if (adapter->eee_advert &
				    hw->dev_spec.ich8lan.eee_lp_ability &
				    I82579_EEE_100_SUPPORTED)
					lpi_ctrl |= I82579_LPI_CTRL_100_ENABLE;
				if (adapter->eee_advert &
				    hw->dev_spec.ich8lan.eee_lp_ability &
				    I82579_EEE_1000_SUPPORTED)
					lpi_ctrl |= I82579_LPI_CTRL_1000_ENABLE;

				retval = e1e_wphy_locked(hw, I82579_LPI_CTRL,
							 lpi_ctrl);
			}
		}
		hw->phy.ops.release(hw);
	}

	/* Release control of h/w to f/w.  If f/w is AMT enabled, this
	 * would have already happened in close and is redundant.
	 */
	e1000e_release_hw_control(adapter);

	pci_clear_master(pdev);

	/* The pci-e switch on some quad port adapters will report a
	 * correctable error when the MAC transitions from D0 to D3.  To
	 * prevent this we need to mask off the correctable errors on the
	 * downstream port of the pci-e switch.
	 *
	 * We don't have the associated upstream bridge while assigning
	 * the PCI device into guest. For example, the KVM on power is
	 * one of the cases.
	 */
	if (adapter->flags & FLAG_IS_QUAD_PORT) {
		struct pci_dev *us_dev = pdev->bus->self;
		u16 devctl;

		if (!us_dev)
			return 0;

		pcie_capability_read_word(us_dev, PCI_EXP_DEVCTL, &devctl);
		pcie_capability_write_word(us_dev, PCI_EXP_DEVCTL,
					   (devctl & ~PCI_EXP_DEVCTL_CERE));

		pci_save_state(pdev);
		pci_prepare_to_sleep(pdev);

		pcie_capability_write_word(us_dev, PCI_EXP_DEVCTL, devctl);
	}

	return 0;
}