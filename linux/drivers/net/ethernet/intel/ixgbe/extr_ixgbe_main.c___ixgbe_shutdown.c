#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct pci_dev {int dummy; } ;
struct net_device {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* set_phy_power ) (struct ixgbe_hw*,int) ;} ;
struct TYPE_8__ {TYPE_3__ ops; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* enable_tx_laser ) (struct ixgbe_hw*) ;int /*<<< orphan*/  (* stop_link_on_d3 ) (struct ixgbe_hw*) ;} ;
struct TYPE_6__ {int type; TYPE_1__ ops; } ;
struct ixgbe_hw {TYPE_4__ phy; TYPE_2__ mac; } ;
struct ixgbe_adapter {int wol; int /*<<< orphan*/  state; struct ixgbe_hw hw; struct net_device* netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IXGBE_CTRL ; 
 int IXGBE_CTRL_GIO_DIS ; 
 int /*<<< orphan*/  IXGBE_FCTRL ; 
 int IXGBE_FCTRL_MPE ; 
 int IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IXGBE_WUC ; 
 int /*<<< orphan*/  IXGBE_WUFC ; 
 int /*<<< orphan*/  __IXGBE_DISABLED ; 
 int /*<<< orphan*/  ixgbe_clear_interrupt_scheme (struct ixgbe_adapter*) ; 
 int /*<<< orphan*/  ixgbe_close_suspend (struct ixgbe_adapter*) ; 
#define  ixgbe_mac_82598EB 133 
#define  ixgbe_mac_82599EB 132 
#define  ixgbe_mac_X540 131 
#define  ixgbe_mac_X550 130 
#define  ixgbe_mac_X550EM_x 129 
#define  ixgbe_mac_x550em_a 128 
 int /*<<< orphan*/  ixgbe_release_hw_control (struct ixgbe_adapter*) ; 
 int /*<<< orphan*/  ixgbe_set_rx_mode (struct net_device*) ; 
 int /*<<< orphan*/  netif_device_detach (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct ixgbe_adapter* pci_get_drvdata (struct pci_dev*) ; 
 int pci_save_state (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_wake_from_d3 (struct pci_dev*,int) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 int /*<<< orphan*/  stub1 (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  stub2 (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  stub3 (struct ixgbe_hw*,int) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __ixgbe_shutdown(struct pci_dev *pdev, bool *enable_wake)
{
	struct ixgbe_adapter *adapter = pci_get_drvdata(pdev);
	struct net_device *netdev = adapter->netdev;
	struct ixgbe_hw *hw = &adapter->hw;
	u32 ctrl;
	u32 wufc = adapter->wol;
#ifdef CONFIG_PM
	int retval = 0;
#endif

	rtnl_lock();
	netif_device_detach(netdev);

	if (netif_running(netdev))
		ixgbe_close_suspend(adapter);

	ixgbe_clear_interrupt_scheme(adapter);
	rtnl_unlock();

#ifdef CONFIG_PM
	retval = pci_save_state(pdev);
	if (retval)
		return retval;

#endif
	if (hw->mac.ops.stop_link_on_d3)
		hw->mac.ops.stop_link_on_d3(hw);

	if (wufc) {
		u32 fctrl;

		ixgbe_set_rx_mode(netdev);

		/* enable the optics for 82599 SFP+ fiber as we can WoL */
		if (hw->mac.ops.enable_tx_laser)
			hw->mac.ops.enable_tx_laser(hw);

		/* enable the reception of multicast packets */
		fctrl = IXGBE_READ_REG(hw, IXGBE_FCTRL);
		fctrl |= IXGBE_FCTRL_MPE;
		IXGBE_WRITE_REG(hw, IXGBE_FCTRL, fctrl);

		ctrl = IXGBE_READ_REG(hw, IXGBE_CTRL);
		ctrl |= IXGBE_CTRL_GIO_DIS;
		IXGBE_WRITE_REG(hw, IXGBE_CTRL, ctrl);

		IXGBE_WRITE_REG(hw, IXGBE_WUFC, wufc);
	} else {
		IXGBE_WRITE_REG(hw, IXGBE_WUC, 0);
		IXGBE_WRITE_REG(hw, IXGBE_WUFC, 0);
	}

	switch (hw->mac.type) {
	case ixgbe_mac_82598EB:
		pci_wake_from_d3(pdev, false);
		break;
	case ixgbe_mac_82599EB:
	case ixgbe_mac_X540:
	case ixgbe_mac_X550:
	case ixgbe_mac_X550EM_x:
	case ixgbe_mac_x550em_a:
		pci_wake_from_d3(pdev, !!wufc);
		break;
	default:
		break;
	}

	*enable_wake = !!wufc;
	if (hw->phy.ops.set_phy_power && !*enable_wake)
		hw->phy.ops.set_phy_power(hw, false);

	ixgbe_release_hw_control(adapter);

	if (!test_and_set_bit(__IXGBE_DISABLED, &adapter->state))
		pci_disable_device(pdev);

	return 0;
}