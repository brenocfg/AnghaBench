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
typedef  int u8 ;
struct net_device {int flags; } ;
struct hnae3_handle {int netdev_flags; } ;

/* Variables and functions */
 int ENOSPC ; 
 int HNAE3_OVERFLOW_MPE ; 
 int HNAE3_OVERFLOW_UPE ; 
 int HNAE3_VLAN_FLTR ; 
 int IFF_MULTICAST ; 
 int __dev_mc_sync (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int __dev_uc_sync (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hns3_enable_vlan_filter (struct net_device*,int) ; 
 struct hnae3_handle* hns3_get_handle (struct net_device*) ; 
 int hns3_get_netdev_flags (struct net_device*) ; 
 int /*<<< orphan*/  hns3_nic_mc_sync ; 
 int /*<<< orphan*/  hns3_nic_mc_unsync ; 
 int /*<<< orphan*/  hns3_nic_uc_sync ; 
 int /*<<< orphan*/  hns3_nic_uc_unsync ; 
 int /*<<< orphan*/  hns3_update_promisc_mode (struct net_device*,int) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 

__attribute__((used)) static void hns3_nic_set_rx_mode(struct net_device *netdev)
{
	struct hnae3_handle *h = hns3_get_handle(netdev);
	u8 new_flags;
	int ret;

	new_flags = hns3_get_netdev_flags(netdev);

	ret = __dev_uc_sync(netdev, hns3_nic_uc_sync, hns3_nic_uc_unsync);
	if (ret) {
		netdev_err(netdev, "sync uc address fail\n");
		if (ret == -ENOSPC)
			new_flags |= HNAE3_OVERFLOW_UPE;
	}

	if (netdev->flags & IFF_MULTICAST) {
		ret = __dev_mc_sync(netdev, hns3_nic_mc_sync,
				    hns3_nic_mc_unsync);
		if (ret) {
			netdev_err(netdev, "sync mc address fail\n");
			if (ret == -ENOSPC)
				new_flags |= HNAE3_OVERFLOW_MPE;
		}
	}

	/* User mode Promisc mode enable and vlan filtering is disabled to
	 * let all packets in. MAC-VLAN Table overflow Promisc enabled and
	 * vlan fitering is enabled
	 */
	hns3_enable_vlan_filter(netdev, new_flags & HNAE3_VLAN_FLTR);
	h->netdev_flags = new_flags;
	hns3_update_promisc_mode(netdev, new_flags);
}