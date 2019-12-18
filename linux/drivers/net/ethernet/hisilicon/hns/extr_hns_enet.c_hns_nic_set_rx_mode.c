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
struct hns_nic_priv {struct hnae_handle* ae_handle; } ;
struct hnae_handle {TYPE_2__* dev; } ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* set_promisc_mode ) (struct hnae_handle*,int) ;} ;

/* Variables and functions */
 int IFF_PROMISC ; 
 scalar_t__ __dev_uc_sync (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hns_nic_uc_sync ; 
 int /*<<< orphan*/  hns_nic_uc_unsync ; 
 int /*<<< orphan*/  hns_set_multicast_list (struct net_device*) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct hns_nic_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  stub1 (struct hnae_handle*,int) ; 
 int /*<<< orphan*/  stub2 (struct hnae_handle*,int) ; 

__attribute__((used)) static void hns_nic_set_rx_mode(struct net_device *ndev)
{
	struct hns_nic_priv *priv = netdev_priv(ndev);
	struct hnae_handle *h = priv->ae_handle;

	if (h->dev->ops->set_promisc_mode) {
		if (ndev->flags & IFF_PROMISC)
			h->dev->ops->set_promisc_mode(h, 1);
		else
			h->dev->ops->set_promisc_mode(h, 0);
	}

	hns_set_multicast_list(ndev);

	if (__dev_uc_sync(ndev, hns_nic_uc_sync, hns_nic_uc_unsync))
		netdev_err(ndev, "sync uc address fail\n");
}