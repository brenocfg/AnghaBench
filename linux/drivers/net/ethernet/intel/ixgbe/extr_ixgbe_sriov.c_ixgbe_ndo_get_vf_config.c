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
struct net_device {int dummy; } ;
struct ixgbe_adapter {int num_vfs; TYPE_1__* vfinfo; } ;
struct ifla_vf_info {int vf; int /*<<< orphan*/  trusted; int /*<<< orphan*/  rss_query_en; int /*<<< orphan*/  spoofchk; int /*<<< orphan*/  qos; int /*<<< orphan*/  vlan; scalar_t__ min_tx_rate; int /*<<< orphan*/  max_tx_rate; int /*<<< orphan*/  mac; } ;
struct TYPE_2__ {int /*<<< orphan*/  trusted; int /*<<< orphan*/  rss_query_enabled; int /*<<< orphan*/  spoofchk_enabled; int /*<<< orphan*/  pf_qos; int /*<<< orphan*/  pf_vlan; int /*<<< orphan*/  tx_rate; int /*<<< orphan*/  vf_mac_addresses; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ixgbe_adapter* netdev_priv (struct net_device*) ; 

int ixgbe_ndo_get_vf_config(struct net_device *netdev,
			    int vf, struct ifla_vf_info *ivi)
{
	struct ixgbe_adapter *adapter = netdev_priv(netdev);
	if (vf >= adapter->num_vfs)
		return -EINVAL;
	ivi->vf = vf;
	memcpy(&ivi->mac, adapter->vfinfo[vf].vf_mac_addresses, ETH_ALEN);
	ivi->max_tx_rate = adapter->vfinfo[vf].tx_rate;
	ivi->min_tx_rate = 0;
	ivi->vlan = adapter->vfinfo[vf].pf_vlan;
	ivi->qos = adapter->vfinfo[vf].pf_qos;
	ivi->spoofchk = adapter->vfinfo[vf].spoofchk_enabled;
	ivi->rss_query_en = adapter->vfinfo[vf].rss_query_enabled;
	ivi->trusted = adapter->vfinfo[vf].trusted;
	return 0;
}