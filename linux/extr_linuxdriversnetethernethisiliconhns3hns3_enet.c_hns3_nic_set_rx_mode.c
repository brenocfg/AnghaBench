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
struct net_device {int flags; } ;
struct hnae3_handle {TYPE_2__* ae_algo; } ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* update_mta_status ) (struct hnae3_handle*) ;int /*<<< orphan*/  (* set_promisc_mode ) (struct hnae3_handle*,int,int) ;} ;

/* Variables and functions */
 int IFF_ALLMULTI ; 
 int IFF_MULTICAST ; 
 int IFF_PROMISC ; 
 scalar_t__ __dev_mc_sync (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ __dev_uc_sync (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct hnae3_handle* hns3_get_handle (struct net_device*) ; 
 int /*<<< orphan*/  hns3_nic_mc_sync ; 
 int /*<<< orphan*/  hns3_nic_mc_unsync ; 
 int /*<<< orphan*/  hns3_nic_uc_sync ; 
 int /*<<< orphan*/  hns3_nic_uc_unsync ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 int /*<<< orphan*/  stub1 (struct hnae3_handle*,int,int) ; 
 int /*<<< orphan*/  stub2 (struct hnae3_handle*,int,int) ; 
 int /*<<< orphan*/  stub3 (struct hnae3_handle*,int,int) ; 
 int /*<<< orphan*/  stub4 (struct hnae3_handle*) ; 

__attribute__((used)) static void hns3_nic_set_rx_mode(struct net_device *netdev)
{
	struct hnae3_handle *h = hns3_get_handle(netdev);

	if (h->ae_algo->ops->set_promisc_mode) {
		if (netdev->flags & IFF_PROMISC)
			h->ae_algo->ops->set_promisc_mode(h, true, true);
		else if (netdev->flags & IFF_ALLMULTI)
			h->ae_algo->ops->set_promisc_mode(h, false, true);
		else
			h->ae_algo->ops->set_promisc_mode(h, false, false);
	}
	if (__dev_uc_sync(netdev, hns3_nic_uc_sync, hns3_nic_uc_unsync))
		netdev_err(netdev, "sync uc address fail\n");
	if (netdev->flags & IFF_MULTICAST) {
		if (__dev_mc_sync(netdev, hns3_nic_mc_sync, hns3_nic_mc_unsync))
			netdev_err(netdev, "sync mc address fail\n");

		if (h->ae_algo->ops->update_mta_status)
			h->ae_algo->ops->update_mta_status(h);
	}
}