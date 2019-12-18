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
struct pci_dev {int dummy; } ;
struct net_device {int dummy; } ;
struct e1000_hw {scalar_t__ mac_type; scalar_t__ media_type; } ;
struct e1000_adapter {int wol; int /*<<< orphan*/  flags; scalar_t__ en_mng_pt; struct e1000_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTRL ; 
 int /*<<< orphan*/  CTRL_EXT ; 
 int E1000_CHECK_RESET_COUNT ; 
 int E1000_CTRL_ADVD3WUC ; 
 int E1000_CTRL_EN_PHY_PWR_MGMT ; 
 int E1000_CTRL_EXT_SDP7_DATA ; 
 int E1000_RCTL_EN ; 
 int E1000_RCTL_MPE ; 
 int E1000_STATUS_LU ; 
 int E1000_WUC_PME_EN ; 
 int E1000_WUFC_LNKC ; 
 int E1000_WUFC_MC ; 
 int /*<<< orphan*/  RCTL ; 
 int /*<<< orphan*/  STATUS ; 
 int /*<<< orphan*/  WARN_ON (scalar_t__) ; 
 int /*<<< orphan*/  WUC ; 
 int /*<<< orphan*/  WUFC ; 
 int /*<<< orphan*/  __E1000_DISABLED ; 
 int /*<<< orphan*/  __E1000_RESETTING ; 
 scalar_t__ e1000_82540 ; 
 int /*<<< orphan*/  e1000_down (struct e1000_adapter*) ; 
 int /*<<< orphan*/  e1000_free_irq (struct e1000_adapter*) ; 
 scalar_t__ e1000_media_type_fiber ; 
 scalar_t__ e1000_media_type_internal_serdes ; 
 int /*<<< orphan*/  e1000_release_manageability (struct e1000_adapter*) ; 
 int /*<<< orphan*/  e1000_set_rx_mode (struct net_device*) ; 
 int /*<<< orphan*/  e1000_setup_rctl (struct e1000_adapter*) ; 
 int er32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ew32 (int /*<<< orphan*/ ,int) ; 
 struct e1000_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_device_detach (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct net_device* pci_get_drvdata (struct pci_dev*) ; 
 int pci_save_state (struct pci_dev*) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int __e1000_shutdown(struct pci_dev *pdev, bool *enable_wake)
{
	struct net_device *netdev = pci_get_drvdata(pdev);
	struct e1000_adapter *adapter = netdev_priv(netdev);
	struct e1000_hw *hw = &adapter->hw;
	u32 ctrl, ctrl_ext, rctl, status;
	u32 wufc = adapter->wol;
#ifdef CONFIG_PM
	int retval = 0;
#endif

	netif_device_detach(netdev);

	if (netif_running(netdev)) {
		int count = E1000_CHECK_RESET_COUNT;

		while (test_bit(__E1000_RESETTING, &adapter->flags) && count--)
			usleep_range(10000, 20000);

		WARN_ON(test_bit(__E1000_RESETTING, &adapter->flags));
		e1000_down(adapter);
	}

#ifdef CONFIG_PM
	retval = pci_save_state(pdev);
	if (retval)
		return retval;
#endif

	status = er32(STATUS);
	if (status & E1000_STATUS_LU)
		wufc &= ~E1000_WUFC_LNKC;

	if (wufc) {
		e1000_setup_rctl(adapter);
		e1000_set_rx_mode(netdev);

		rctl = er32(RCTL);

		/* turn on all-multi mode if wake on multicast is enabled */
		if (wufc & E1000_WUFC_MC)
			rctl |= E1000_RCTL_MPE;

		/* enable receives in the hardware */
		ew32(RCTL, rctl | E1000_RCTL_EN);

		if (hw->mac_type >= e1000_82540) {
			ctrl = er32(CTRL);
			/* advertise wake from D3Cold */
			#define E1000_CTRL_ADVD3WUC 0x00100000
			/* phy power management enable */
			#define E1000_CTRL_EN_PHY_PWR_MGMT 0x00200000
			ctrl |= E1000_CTRL_ADVD3WUC |
				E1000_CTRL_EN_PHY_PWR_MGMT;
			ew32(CTRL, ctrl);
		}

		if (hw->media_type == e1000_media_type_fiber ||
		    hw->media_type == e1000_media_type_internal_serdes) {
			/* keep the laser running in D3 */
			ctrl_ext = er32(CTRL_EXT);
			ctrl_ext |= E1000_CTRL_EXT_SDP7_DATA;
			ew32(CTRL_EXT, ctrl_ext);
		}

		ew32(WUC, E1000_WUC_PME_EN);
		ew32(WUFC, wufc);
	} else {
		ew32(WUC, 0);
		ew32(WUFC, 0);
	}

	e1000_release_manageability(adapter);

	*enable_wake = !!wufc;

	/* make sure adapter isn't asleep if manageability is enabled */
	if (adapter->en_mng_pt)
		*enable_wake = true;

	if (netif_running(netdev))
		e1000_free_irq(adapter);

	if (!test_and_set_bit(__E1000_DISABLED, &adapter->flags))
		pci_disable_device(pdev);

	return 0;
}