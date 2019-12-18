#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct net_device {int dummy; } ;
struct TYPE_4__ {int max_epid; int my_epid; TYPE_1__* ep_shm_info; } ;
struct fjes_adapter {TYPE_2__ hw; } ;
typedef  int /*<<< orphan*/  __be16 ;
struct TYPE_3__ {int /*<<< orphan*/  tx; } ;

/* Variables and functions */
 int ENOSPC ; 
 int /*<<< orphan*/  fjes_hw_check_vlan_id (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int fjes_hw_set_vlan_id (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct fjes_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int fjes_vlan_rx_add_vid(struct net_device *netdev,
				__be16 proto, u16 vid)
{
	struct fjes_adapter *adapter = netdev_priv(netdev);
	bool ret = true;
	int epid;

	for (epid = 0; epid < adapter->hw.max_epid; epid++) {
		if (epid == adapter->hw.my_epid)
			continue;

		if (!fjes_hw_check_vlan_id(
			&adapter->hw.ep_shm_info[epid].tx, vid))
			ret = fjes_hw_set_vlan_id(
				&adapter->hw.ep_shm_info[epid].tx, vid);
	}

	return ret ? 0 : -ENOSPC;
}