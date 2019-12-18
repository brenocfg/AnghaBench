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
struct netxen_minidump {int /*<<< orphan*/  md_capture_mask; int /*<<< orphan*/  md_enabled; int /*<<< orphan*/  md_dump_size; } ;
struct netxen_adapter {int /*<<< orphan*/  fw_version; scalar_t__ fw_mdump_rdy; struct netxen_minidump mdump; } ;
struct net_device {int dummy; } ;
struct ethtool_dump {int /*<<< orphan*/  version; int /*<<< orphan*/  flag; int /*<<< orphan*/  len; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_FW_DUMP_DISABLE ; 
 struct netxen_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int
netxen_get_dump_flag(struct net_device *netdev, struct ethtool_dump *dump)
{
	struct netxen_adapter *adapter = netdev_priv(netdev);
	struct netxen_minidump *mdump = &adapter->mdump;
	if (adapter->fw_mdump_rdy)
		dump->len = mdump->md_dump_size;
	else
		dump->len = 0;

	if (!mdump->md_enabled)
		dump->flag = ETH_FW_DUMP_DISABLE;
	else
		dump->flag = mdump->md_capture_mask;

	dump->version = adapter->fw_version;
	return 0;
}