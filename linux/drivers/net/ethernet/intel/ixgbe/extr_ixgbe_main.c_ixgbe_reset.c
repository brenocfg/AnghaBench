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
struct net_device {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* set_phy_power ) (struct ixgbe_hw*,int) ;} ;
struct TYPE_8__ {TYPE_3__ ops; } ;
struct TYPE_5__ {int (* init_hw ) (struct ixgbe_hw*) ;int /*<<< orphan*/  (* set_vmdq_san_mac ) (struct ixgbe_hw*,int /*<<< orphan*/ ) ;} ;
struct TYPE_6__ {TYPE_1__ ops; scalar_t__ san_mac_rar_index; } ;
struct ixgbe_hw {TYPE_4__ phy; TYPE_2__ mac; int /*<<< orphan*/  hw_addr; } ;
struct ixgbe_adapter {int flags2; int /*<<< orphan*/  wol; struct net_device* netdev; int /*<<< orphan*/  state; int /*<<< orphan*/  flags; struct ixgbe_hw hw; } ;

/* Variables and functions */
#define  IXGBE_ERR_EEPROM_VERSION 131 
#define  IXGBE_ERR_MASTER_REQUESTS_PENDING 130 
#define  IXGBE_ERR_SFP_NOT_PRESENT 129 
#define  IXGBE_ERR_SFP_NOT_SUPPORTED 128 
 int IXGBE_FLAG2_SEARCH_FOR_SFP ; 
 int IXGBE_FLAG2_SFP_NEEDS_RESET ; 
 int /*<<< orphan*/  IXGBE_FLAG_NEED_LINK_CONFIG ; 
 int /*<<< orphan*/  VMDQ_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __IXGBE_IN_SFP_INIT ; 
 int /*<<< orphan*/  __IXGBE_PTP_RUNNING ; 
 int /*<<< orphan*/  __dev_uc_unsync (struct net_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  e_dev_err (char*,...) ; 
 int /*<<< orphan*/  e_dev_warn (char*) ; 
 int /*<<< orphan*/  ixgbe_flush_sw_mac_table (struct ixgbe_adapter*) ; 
 int /*<<< orphan*/  ixgbe_mac_set_default_filter (struct ixgbe_adapter*) ; 
 int /*<<< orphan*/  ixgbe_ptp_reset (struct ixgbe_adapter*) ; 
 scalar_t__ ixgbe_removed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 int stub1 (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  stub2 (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct ixgbe_hw*,int) ; 
 int /*<<< orphan*/  stub4 (struct ixgbe_hw*,int) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

void ixgbe_reset(struct ixgbe_adapter *adapter)
{
	struct ixgbe_hw *hw = &adapter->hw;
	struct net_device *netdev = adapter->netdev;
	int err;

	if (ixgbe_removed(hw->hw_addr))
		return;
	/* lock SFP init bit to prevent race conditions with the watchdog */
	while (test_and_set_bit(__IXGBE_IN_SFP_INIT, &adapter->state))
		usleep_range(1000, 2000);

	/* clear all SFP and link config related flags while holding SFP_INIT */
	adapter->flags2 &= ~(IXGBE_FLAG2_SEARCH_FOR_SFP |
			     IXGBE_FLAG2_SFP_NEEDS_RESET);
	adapter->flags &= ~IXGBE_FLAG_NEED_LINK_CONFIG;

	err = hw->mac.ops.init_hw(hw);
	switch (err) {
	case 0:
	case IXGBE_ERR_SFP_NOT_PRESENT:
	case IXGBE_ERR_SFP_NOT_SUPPORTED:
		break;
	case IXGBE_ERR_MASTER_REQUESTS_PENDING:
		e_dev_err("master disable timed out\n");
		break;
	case IXGBE_ERR_EEPROM_VERSION:
		/* We are running on a pre-production device, log a warning */
		e_dev_warn("This device is a pre-production adapter/LOM. "
			   "Please be aware there may be issues associated with "
			   "your hardware.  If you are experiencing problems "
			   "please contact your Intel or hardware "
			   "representative who provided you with this "
			   "hardware.\n");
		break;
	default:
		e_dev_err("Hardware Error: %d\n", err);
	}

	clear_bit(__IXGBE_IN_SFP_INIT, &adapter->state);

	/* flush entries out of MAC table */
	ixgbe_flush_sw_mac_table(adapter);
	__dev_uc_unsync(netdev, NULL);

	/* do not flush user set addresses */
	ixgbe_mac_set_default_filter(adapter);

	/* update SAN MAC vmdq pool selection */
	if (hw->mac.san_mac_rar_index)
		hw->mac.ops.set_vmdq_san_mac(hw, VMDQ_P(0));

	if (test_bit(__IXGBE_PTP_RUNNING, &adapter->state))
		ixgbe_ptp_reset(adapter);

	if (hw->phy.ops.set_phy_power) {
		if (!netif_running(adapter->netdev) && !adapter->wol)
			hw->phy.ops.set_phy_power(hw, false);
		else
			hw->phy.ops.set_phy_power(hw, true);
	}
}