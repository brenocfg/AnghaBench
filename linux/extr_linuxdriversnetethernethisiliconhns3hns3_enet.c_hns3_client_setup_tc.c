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
typedef  scalar_t__ u8 ;
struct net_device {int dummy; } ;
struct hnae3_knic_private_info {TYPE_1__* dcb_ops; struct net_device* netdev; } ;
struct hnae3_handle {struct hnae3_knic_private_info kinfo; } ;
struct TYPE_2__ {int (* map_update ) (struct hnae3_handle*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int EOPNOTSUPP ; 
 scalar_t__ HNAE3_MAX_TC ; 
 int /*<<< orphan*/  hns3_nic_net_open (struct net_device*) ; 
 int /*<<< orphan*/  hns3_nic_net_stop (struct net_device*) ; 
 int hns3_nic_set_real_num_queue (struct net_device*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int netif_running (struct net_device*) ; 
 int stub1 (struct hnae3_handle*) ; 

__attribute__((used)) static int hns3_client_setup_tc(struct hnae3_handle *handle, u8 tc)
{
	struct hnae3_knic_private_info *kinfo = &handle->kinfo;
	struct net_device *ndev = kinfo->netdev;
	bool if_running;
	int ret;

	if (tc > HNAE3_MAX_TC)
		return -EINVAL;

	if (!ndev)
		return -ENODEV;

	if_running = netif_running(ndev);

	if (if_running) {
		(void)hns3_nic_net_stop(ndev);
		msleep(100);
	}

	ret = (kinfo->dcb_ops && kinfo->dcb_ops->map_update) ?
		kinfo->dcb_ops->map_update(handle) : -EOPNOTSUPP;
	if (ret)
		goto err_out;

	ret = hns3_nic_set_real_num_queue(ndev);

err_out:
	if (if_running)
		(void)hns3_nic_net_open(ndev);

	return ret;
}