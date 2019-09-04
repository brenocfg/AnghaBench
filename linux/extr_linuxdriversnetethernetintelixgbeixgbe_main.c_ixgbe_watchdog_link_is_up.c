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
typedef  int u32 ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int type; } ;
struct ixgbe_hw {TYPE_1__ mac; } ;
struct ixgbe_adapter {int link_speed; struct net_device* netdev; int /*<<< orphan*/  state; int /*<<< orphan*/  last_rx_ptp_check; int /*<<< orphan*/  flags2; struct ixgbe_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  IXGBE_FCCFG ; 
 int IXGBE_FCCFG_TFCE_802_3X ; 
 int /*<<< orphan*/  IXGBE_FCTRL ; 
 int IXGBE_FCTRL_RFCE ; 
 int /*<<< orphan*/  IXGBE_FLAG2_SEARCH_FOR_SFP ; 
#define  IXGBE_LINK_SPEED_100_FULL 139 
#define  IXGBE_LINK_SPEED_10GB_FULL 138 
#define  IXGBE_LINK_SPEED_10_FULL 137 
#define  IXGBE_LINK_SPEED_1GB_FULL 136 
#define  IXGBE_LINK_SPEED_2_5GB_FULL 135 
#define  IXGBE_LINK_SPEED_5GB_FULL 134 
 int /*<<< orphan*/  IXGBE_MFLCN ; 
 int IXGBE_MFLCN_RFCE ; 
 int IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_RMCS ; 
 int IXGBE_RMCS_TFCE_802_3X ; 
 int /*<<< orphan*/  __IXGBE_PTP_RUNNING ; 
 int /*<<< orphan*/  drv ; 
 int /*<<< orphan*/  e_info (int /*<<< orphan*/ ,char*,char const*,char*) ; 
 int /*<<< orphan*/  ixgbe_check_vf_rate_limit (struct ixgbe_adapter*) ; 
#define  ixgbe_mac_82598EB 133 
#define  ixgbe_mac_82599EB 132 
#define  ixgbe_mac_X540 131 
#define  ixgbe_mac_X550 130 
#define  ixgbe_mac_X550EM_x 129 
#define  ixgbe_mac_x550em_a 128 
 int /*<<< orphan*/  ixgbe_ping_all_vfs (struct ixgbe_adapter*) ; 
 int /*<<< orphan*/  ixgbe_ptp_start_cyclecounter (struct ixgbe_adapter*) ; 
 int /*<<< orphan*/  ixgbe_update_default_up (struct ixgbe_adapter*) ; 
 int /*<<< orphan*/  jiffies ; 
 scalar_t__ netif_carrier_ok (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_on (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_wake_all_queues (struct net_device*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ixgbe_watchdog_link_is_up(struct ixgbe_adapter *adapter)
{
	struct net_device *netdev = adapter->netdev;
	struct ixgbe_hw *hw = &adapter->hw;
	u32 link_speed = adapter->link_speed;
	const char *speed_str;
	bool flow_rx, flow_tx;

	/* only continue if link was previously down */
	if (netif_carrier_ok(netdev))
		return;

	adapter->flags2 &= ~IXGBE_FLAG2_SEARCH_FOR_SFP;

	switch (hw->mac.type) {
	case ixgbe_mac_82598EB: {
		u32 frctl = IXGBE_READ_REG(hw, IXGBE_FCTRL);
		u32 rmcs = IXGBE_READ_REG(hw, IXGBE_RMCS);
		flow_rx = !!(frctl & IXGBE_FCTRL_RFCE);
		flow_tx = !!(rmcs & IXGBE_RMCS_TFCE_802_3X);
	}
		break;
	case ixgbe_mac_X540:
	case ixgbe_mac_X550:
	case ixgbe_mac_X550EM_x:
	case ixgbe_mac_x550em_a:
	case ixgbe_mac_82599EB: {
		u32 mflcn = IXGBE_READ_REG(hw, IXGBE_MFLCN);
		u32 fccfg = IXGBE_READ_REG(hw, IXGBE_FCCFG);
		flow_rx = !!(mflcn & IXGBE_MFLCN_RFCE);
		flow_tx = !!(fccfg & IXGBE_FCCFG_TFCE_802_3X);
	}
		break;
	default:
		flow_tx = false;
		flow_rx = false;
		break;
	}

	adapter->last_rx_ptp_check = jiffies;

	if (test_bit(__IXGBE_PTP_RUNNING, &adapter->state))
		ixgbe_ptp_start_cyclecounter(adapter);

	switch (link_speed) {
	case IXGBE_LINK_SPEED_10GB_FULL:
		speed_str = "10 Gbps";
		break;
	case IXGBE_LINK_SPEED_5GB_FULL:
		speed_str = "5 Gbps";
		break;
	case IXGBE_LINK_SPEED_2_5GB_FULL:
		speed_str = "2.5 Gbps";
		break;
	case IXGBE_LINK_SPEED_1GB_FULL:
		speed_str = "1 Gbps";
		break;
	case IXGBE_LINK_SPEED_100_FULL:
		speed_str = "100 Mbps";
		break;
	case IXGBE_LINK_SPEED_10_FULL:
		speed_str = "10 Mbps";
		break;
	default:
		speed_str = "unknown speed";
		break;
	}
	e_info(drv, "NIC Link is Up %s, Flow Control: %s\n", speed_str,
	       ((flow_rx && flow_tx) ? "RX/TX" :
	       (flow_rx ? "RX" :
	       (flow_tx ? "TX" : "None"))));

	netif_carrier_on(netdev);
	ixgbe_check_vf_rate_limit(adapter);

	/* enable transmits */
	netif_tx_wake_all_queues(adapter->netdev);

	/* update the default user priority for VFs */
	ixgbe_update_default_up(adapter);

	/* ping all the active vfs to let them know link has changed */
	ixgbe_ping_all_vfs(adapter);
}