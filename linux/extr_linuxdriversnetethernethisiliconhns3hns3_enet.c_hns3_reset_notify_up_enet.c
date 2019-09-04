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
struct hnae3_knic_private_info {int /*<<< orphan*/  netdev; } ;
struct hnae3_handle {int /*<<< orphan*/  last_reset_time; struct hnae3_knic_private_info kinfo; } ;

/* Variables and functions */
 int hns3_nic_net_up (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ netif_running (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hns3_reset_notify_up_enet(struct hnae3_handle *handle)
{
	struct hnae3_knic_private_info *kinfo = &handle->kinfo;
	int ret = 0;

	if (netif_running(kinfo->netdev)) {
		ret = hns3_nic_net_up(kinfo->netdev);
		if (ret) {
			netdev_err(kinfo->netdev,
				   "hns net up fail, ret=%d!\n", ret);
			return ret;
		}
		handle->last_reset_time = jiffies;
	}

	return ret;
}