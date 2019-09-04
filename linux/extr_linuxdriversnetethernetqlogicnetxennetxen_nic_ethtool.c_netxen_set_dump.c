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
struct netxen_minidump {int md_enabled; int md_capture_mask; } ;
struct netxen_adapter {int /*<<< orphan*/  flags; int /*<<< orphan*/  fw_mdump_rdy; struct netxen_minidump mdump; } ;
struct net_device {int dummy; } ;
struct ethtool_dump {int flag; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int EINVAL ; 
 int* FW_DUMP_LEVELS ; 
 int /*<<< orphan*/  NETXEN_FW_RESET_OWNER ; 
#define  NX_DISABLE_FW_DUMP 131 
#define  NX_ENABLE_FW_DUMP 130 
#define  NX_FORCE_FW_DUMP_KEY 129 
#define  NX_FORCE_FW_RESET 128 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*,...) ; 
 struct netxen_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  nx_dev_request_reset (struct netxen_adapter*) ; 

__attribute__((used)) static int
netxen_set_dump(struct net_device *netdev, struct ethtool_dump *val)
{
	int i;
	struct netxen_adapter *adapter = netdev_priv(netdev);
	struct netxen_minidump *mdump = &adapter->mdump;

	switch (val->flag) {
	case NX_FORCE_FW_DUMP_KEY:
		if (!mdump->md_enabled) {
			netdev_info(netdev, "FW dump not enabled\n");
			return 0;
		}
		if (adapter->fw_mdump_rdy) {
			netdev_info(netdev, "Previous dump not cleared, not forcing dump\n");
			return 0;
		}
		netdev_info(netdev, "Forcing a fw dump\n");
		nx_dev_request_reset(adapter);
		break;
	case NX_DISABLE_FW_DUMP:
		if (mdump->md_enabled) {
			netdev_info(netdev, "Disabling FW Dump\n");
			mdump->md_enabled = 0;
		}
		break;
	case NX_ENABLE_FW_DUMP:
		if (!mdump->md_enabled) {
			netdev_info(netdev, "Enabling FW dump\n");
			mdump->md_enabled = 1;
		}
		break;
	case NX_FORCE_FW_RESET:
		netdev_info(netdev, "Forcing FW reset\n");
		nx_dev_request_reset(adapter);
		adapter->flags &= ~NETXEN_FW_RESET_OWNER;
		break;
	default:
		for (i = 0; i < ARRAY_SIZE(FW_DUMP_LEVELS); i++) {
			if (val->flag == FW_DUMP_LEVELS[i]) {
				mdump->md_capture_mask = val->flag;
				netdev_info(netdev,
					"Driver mask changed to: 0x%x\n",
					mdump->md_capture_mask);
				return 0;
			}
		}
		netdev_info(netdev,
			"Invalid dump level: 0x%x\n", val->flag);
		return -EINVAL;
	}

	return 0;
}