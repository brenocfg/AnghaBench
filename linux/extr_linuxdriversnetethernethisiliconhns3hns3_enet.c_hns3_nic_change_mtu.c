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
struct hnae3_handle {TYPE_1__* ae_algo; } ;
struct TYPE_4__ {int (* set_mtu ) (struct hnae3_handle*,int) ;} ;
struct TYPE_3__ {TYPE_2__* ops; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 struct hnae3_handle* hns3_get_handle (struct net_device*) ; 
 scalar_t__ hns3_nic_net_open (struct net_device*) ; 
 int /*<<< orphan*/  hns3_nic_net_stop (struct net_device*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,int) ; 
 int netif_running (struct net_device*) ; 
 int stub1 (struct hnae3_handle*,int) ; 

__attribute__((used)) static int hns3_nic_change_mtu(struct net_device *netdev, int new_mtu)
{
	struct hnae3_handle *h = hns3_get_handle(netdev);
	bool if_running = netif_running(netdev);
	int ret;

	if (!h->ae_algo->ops->set_mtu)
		return -EOPNOTSUPP;

	/* if this was called with netdev up then bring netdevice down */
	if (if_running) {
		(void)hns3_nic_net_stop(netdev);
		msleep(100);
	}

	ret = h->ae_algo->ops->set_mtu(h, new_mtu);
	if (ret) {
		netdev_err(netdev, "failed to change MTU in hardware %d\n",
			   ret);
		return ret;
	}

	netdev->mtu = new_mtu;

	/* if the netdev was running earlier, bring it up again */
	if (if_running && hns3_nic_net_open(netdev))
		ret = -EINVAL;

	return ret;
}