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
struct pci_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  subsystem_device; int /*<<< orphan*/  subsystem_vendor; int /*<<< orphan*/  revision; int /*<<< orphan*/  device; int /*<<< orphan*/  vendor; } ;
struct net_device {int /*<<< orphan*/  dev_addr; } ;
struct TYPE_7__ {int (* reset_hw ) (struct ixgbe_hw*) ;int (* init_hw ) (struct ixgbe_hw*) ;int (* get_mac_addr ) (struct ixgbe_hw*,int /*<<< orphan*/ ) ;} ;
struct TYPE_8__ {scalar_t__ type; int max_tx_queues; int max_rx_queues; int /*<<< orphan*/  perm_addr; int /*<<< orphan*/  addr; TYPE_3__ ops; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* init_params ) (struct ixgbe_hw*) ;} ;
struct TYPE_6__ {TYPE_1__ ops; } ;
struct ixgbe_hw {TYPE_4__ mac; TYPE_2__ mbx; int /*<<< orphan*/  subsystem_device_id; int /*<<< orphan*/  subsystem_vendor_id; int /*<<< orphan*/  revision_id; int /*<<< orphan*/  device_id; int /*<<< orphan*/  vendor_id; } ;
struct ixgbevf_adapter {int rx_itr_setting; int tx_itr_setting; int /*<<< orphan*/  state; int /*<<< orphan*/  rx_ring_count; int /*<<< orphan*/  tx_ring_count; struct ixgbe_hw hw; int /*<<< orphan*/  mbx_lock; struct net_device* netdev; struct pci_dev* pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IXGBEVF_DEFAULT_RXD ; 
 int /*<<< orphan*/  IXGBEVF_DEFAULT_TXD ; 
 int /*<<< orphan*/  __IXGBEVF_DOWN ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  eth_hw_addr_random (struct net_device*) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_valid_ether_addr (int /*<<< orphan*/ ) ; 
 scalar_t__ is_zero_ether_addr (int /*<<< orphan*/ ) ; 
 scalar_t__ ixgbe_mac_X550_vf ; 
 int ixgbevf_init_rss_key (struct ixgbevf_adapter*) ; 
 int /*<<< orphan*/  ixgbevf_negotiate_api (struct ixgbevf_adapter*) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct ixgbe_hw*) ; 
 int stub2 (struct ixgbe_hw*) ; 
 int stub3 (struct ixgbe_hw*) ; 
 int stub4 (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ixgbevf_sw_init(struct ixgbevf_adapter *adapter)
{
	struct ixgbe_hw *hw = &adapter->hw;
	struct pci_dev *pdev = adapter->pdev;
	struct net_device *netdev = adapter->netdev;
	int err;

	/* PCI config space info */
	hw->vendor_id = pdev->vendor;
	hw->device_id = pdev->device;
	hw->revision_id = pdev->revision;
	hw->subsystem_vendor_id = pdev->subsystem_vendor;
	hw->subsystem_device_id = pdev->subsystem_device;

	hw->mbx.ops.init_params(hw);

	if (hw->mac.type >= ixgbe_mac_X550_vf) {
		err = ixgbevf_init_rss_key(adapter);
		if (err)
			goto out;
	}

	/* assume legacy case in which PF would only give VF 2 queues */
	hw->mac.max_tx_queues = 2;
	hw->mac.max_rx_queues = 2;

	/* lock to protect mailbox accesses */
	spin_lock_init(&adapter->mbx_lock);

	err = hw->mac.ops.reset_hw(hw);
	if (err) {
		dev_info(&pdev->dev,
			 "PF still in reset state.  Is the PF interface up?\n");
	} else {
		err = hw->mac.ops.init_hw(hw);
		if (err) {
			pr_err("init_shared_code failed: %d\n", err);
			goto out;
		}
		ixgbevf_negotiate_api(adapter);
		err = hw->mac.ops.get_mac_addr(hw, hw->mac.addr);
		if (err)
			dev_info(&pdev->dev, "Error reading MAC address\n");
		else if (is_zero_ether_addr(adapter->hw.mac.addr))
			dev_info(&pdev->dev,
				 "MAC address not assigned by administrator.\n");
		ether_addr_copy(netdev->dev_addr, hw->mac.addr);
	}

	if (!is_valid_ether_addr(netdev->dev_addr)) {
		dev_info(&pdev->dev, "Assigning random MAC address\n");
		eth_hw_addr_random(netdev);
		ether_addr_copy(hw->mac.addr, netdev->dev_addr);
		ether_addr_copy(hw->mac.perm_addr, netdev->dev_addr);
	}

	/* Enable dynamic interrupt throttling rates */
	adapter->rx_itr_setting = 1;
	adapter->tx_itr_setting = 1;

	/* set default ring sizes */
	adapter->tx_ring_count = IXGBEVF_DEFAULT_TXD;
	adapter->rx_ring_count = IXGBEVF_DEFAULT_RXD;

	set_bit(__IXGBEVF_DOWN, &adapter->state);
	return 0;

out:
	return err;
}