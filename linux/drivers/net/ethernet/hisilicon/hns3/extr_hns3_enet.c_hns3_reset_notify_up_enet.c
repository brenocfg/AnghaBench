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
struct hns3_nic_priv {int /*<<< orphan*/  state; } ;
struct hnae3_knic_private_info {int /*<<< orphan*/  netdev; } ;
struct hnae3_handle {struct hnae3_knic_private_info kinfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  HNS3_NIC_STATE_RESETTING ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int hns3_nic_net_open (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,int) ; 
 struct hns3_nic_priv* netdev_priv (int /*<<< orphan*/ ) ; 
 scalar_t__ netif_running (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hns3_reset_notify_up_enet(struct hnae3_handle *handle)
{
	struct hnae3_knic_private_info *kinfo = &handle->kinfo;
	struct hns3_nic_priv *priv = netdev_priv(kinfo->netdev);
	int ret = 0;

	clear_bit(HNS3_NIC_STATE_RESETTING, &priv->state);

	if (netif_running(kinfo->netdev)) {
		ret = hns3_nic_net_open(kinfo->netdev);
		if (ret) {
			set_bit(HNS3_NIC_STATE_RESETTING, &priv->state);
			netdev_err(kinfo->netdev,
				   "net up fail, ret=%d!\n", ret);
			return ret;
		}
	}

	return ret;
}