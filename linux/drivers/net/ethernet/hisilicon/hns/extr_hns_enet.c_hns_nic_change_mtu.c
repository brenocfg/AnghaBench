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
struct net_device {int mtu; } ;
struct hns_nic_priv {scalar_t__ enet_ver; struct hnae_handle* ae_handle; } ;
struct hnae_handle {TYPE_2__* dev; } ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {int (* set_mtu ) (struct hnae_handle*,int) ;} ;

/* Variables and functions */
 scalar_t__ AE_VERSION_1 ; 
 int BD_SIZE_2048_MAX_MTU ; 
 int EINVAL ; 
 int ENOTSUPP ; 
 int /*<<< orphan*/  hnae_reinit_all_ring_desc (struct hnae_handle*) ; 
 int /*<<< orphan*/  hnae_reinit_all_ring_page_off (struct hnae_handle*) ; 
 int hns_nic_clear_all_rx_fetch (struct net_device*) ; 
 scalar_t__ hns_nic_net_open (struct net_device*) ; 
 int /*<<< orphan*/  hns_nic_net_stop (struct net_device*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,...) ; 
 struct hns_nic_priv* netdev_priv (struct net_device*) ; 
 int netif_running (struct net_device*) ; 
 int stub1 (struct hnae_handle*,int) ; 

__attribute__((used)) static int hns_nic_change_mtu(struct net_device *ndev, int new_mtu)
{
	struct hns_nic_priv *priv = netdev_priv(ndev);
	struct hnae_handle *h = priv->ae_handle;
	bool if_running = netif_running(ndev);
	int ret;

	/* MTU < 68 is an error and causes problems on some kernels */
	if (new_mtu < 68)
		return -EINVAL;

	/* MTU no change */
	if (new_mtu == ndev->mtu)
		return 0;

	if (!h->dev->ops->set_mtu)
		return -ENOTSUPP;

	if (if_running) {
		(void)hns_nic_net_stop(ndev);
		msleep(100);
	}

	if (priv->enet_ver != AE_VERSION_1 &&
	    ndev->mtu <= BD_SIZE_2048_MAX_MTU &&
	    new_mtu > BD_SIZE_2048_MAX_MTU) {
		/* update desc */
		hnae_reinit_all_ring_desc(h);

		/* clear the package which the chip has fetched */
		ret = hns_nic_clear_all_rx_fetch(ndev);

		/* the page offset must be consist with desc */
		hnae_reinit_all_ring_page_off(h);

		if (ret) {
			netdev_err(ndev, "clear the fetched desc fail\n");
			goto out;
		}
	}

	ret = h->dev->ops->set_mtu(h, new_mtu);
	if (ret) {
		netdev_err(ndev, "set mtu fail, return value %d\n",
			   ret);
		goto out;
	}

	/* finally, set new mtu to netdevice */
	ndev->mtu = new_mtu;

out:
	if (if_running) {
		if (hns_nic_net_open(ndev)) {
			netdev_err(ndev, "hns net open fail\n");
			ret = -EINVAL;
		}
	}

	return ret;
}