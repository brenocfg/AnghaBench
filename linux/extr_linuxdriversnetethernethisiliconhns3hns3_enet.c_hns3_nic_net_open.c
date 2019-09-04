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
struct hns3_nic_priv {TYPE_1__* ae_handle; } ;
struct hnae3_knic_private_info {int /*<<< orphan*/ * prio_tc; } ;
struct hnae3_handle {struct hnae3_knic_private_info kinfo; } ;
struct TYPE_2__ {int /*<<< orphan*/  last_reset_time; } ;

/* Variables and functions */
 int HNAE3_MAX_USER_PRIO ; 
 struct hnae3_handle* hns3_get_handle (struct net_device*) ; 
 int hns3_nic_net_up (struct net_device*) ; 
 int hns3_nic_set_real_num_queue (struct net_device*) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,int) ; 
 struct hns3_nic_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_set_prio_tc_map (struct net_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 

__attribute__((used)) static int hns3_nic_net_open(struct net_device *netdev)
{
	struct hns3_nic_priv *priv = netdev_priv(netdev);
	struct hnae3_handle *h = hns3_get_handle(netdev);
	struct hnae3_knic_private_info *kinfo;
	int i, ret;

	netif_carrier_off(netdev);

	ret = hns3_nic_set_real_num_queue(netdev);
	if (ret)
		return ret;

	ret = hns3_nic_net_up(netdev);
	if (ret) {
		netdev_err(netdev,
			   "hns net up fail, ret=%d!\n", ret);
		return ret;
	}

	kinfo = &h->kinfo;
	for (i = 0; i < HNAE3_MAX_USER_PRIO; i++) {
		netdev_set_prio_tc_map(netdev, i,
				       kinfo->prio_tc[i]);
	}

	priv->ae_handle->last_reset_time = jiffies;
	return 0;
}