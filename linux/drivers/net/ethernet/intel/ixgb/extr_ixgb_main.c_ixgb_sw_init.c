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
struct pci_dev {scalar_t__ device; int /*<<< orphan*/  subsystem_device; int /*<<< orphan*/  subsystem_vendor; int /*<<< orphan*/  vendor; } ;
struct net_device {scalar_t__ mtu; } ;
struct TYPE_2__ {int send_xon; } ;
struct ixgb_hw {scalar_t__ device_id; TYPE_1__ fc; int /*<<< orphan*/  mac_type; scalar_t__ max_frame_size; int /*<<< orphan*/  subsystem_id; int /*<<< orphan*/  subsystem_vendor_id; int /*<<< orphan*/  vendor_id; } ;
struct ixgb_adapter {int /*<<< orphan*/  flags; struct net_device* netdev; scalar_t__ rx_buffer_len; struct pci_dev* pdev; struct ixgb_hw hw; } ;

/* Variables and functions */
 scalar_t__ ENET_FCS_LENGTH ; 
 scalar_t__ ENET_HEADER_SIZE ; 
 scalar_t__ IXGB_DEVICE_ID_82597EX ; 
 scalar_t__ IXGB_DEVICE_ID_82597EX_CX4 ; 
 scalar_t__ IXGB_DEVICE_ID_82597EX_LR ; 
 scalar_t__ IXGB_DEVICE_ID_82597EX_SR ; 
 int /*<<< orphan*/  __IXGB_DOWN ; 
 int /*<<< orphan*/  ixgb_82597 ; 
 int /*<<< orphan*/  netif_err (struct ixgb_adapter*,int /*<<< orphan*/ ,struct net_device*,char*) ; 
 int /*<<< orphan*/  probe ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ixgb_sw_init(struct ixgb_adapter *adapter)
{
	struct ixgb_hw *hw = &adapter->hw;
	struct net_device *netdev = adapter->netdev;
	struct pci_dev *pdev = adapter->pdev;

	/* PCI config space info */

	hw->vendor_id = pdev->vendor;
	hw->device_id = pdev->device;
	hw->subsystem_vendor_id = pdev->subsystem_vendor;
	hw->subsystem_id = pdev->subsystem_device;

	hw->max_frame_size = netdev->mtu + ENET_HEADER_SIZE + ENET_FCS_LENGTH;
	adapter->rx_buffer_len = hw->max_frame_size + 8; /* + 8 for errata */

	if ((hw->device_id == IXGB_DEVICE_ID_82597EX) ||
	    (hw->device_id == IXGB_DEVICE_ID_82597EX_CX4) ||
	    (hw->device_id == IXGB_DEVICE_ID_82597EX_LR) ||
	    (hw->device_id == IXGB_DEVICE_ID_82597EX_SR))
		hw->mac_type = ixgb_82597;
	else {
		/* should never have loaded on this device */
		netif_err(adapter, probe, adapter->netdev, "unsupported device id\n");
	}

	/* enable flow control to be programmed */
	hw->fc.send_xon = 1;

	set_bit(__IXGB_DOWN, &adapter->flags);
	return 0;
}