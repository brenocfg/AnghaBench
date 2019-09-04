#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct net_device {int /*<<< orphan*/  dev; } ;
struct hns3_nic_priv {TYPE_3__* tqp_vector; } ;
struct hns3_enet_coalesce {int dummy; } ;
struct hnae3_knic_private_info {scalar_t__ num_tc; scalar_t__ num_tqps; } ;
struct hnae3_handle {struct hnae3_knic_private_info kinfo; } ;
struct ethtool_channels {scalar_t__ combined_count; scalar_t__ tx_count; scalar_t__ rx_count; } ;
struct TYPE_5__ {int /*<<< orphan*/  coal; } ;
struct TYPE_4__ {int /*<<< orphan*/  coal; } ;
struct TYPE_6__ {TYPE_2__ rx_group; TYPE_1__ tx_group; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ hns3_adjust_tqps_num (scalar_t__,scalar_t__) ; 
 struct hnae3_handle* hns3_get_handle (struct net_device*) ; 
 scalar_t__ hns3_get_max_available_channels (struct hnae3_handle*) ; 
 int hns3_modify_tqp_num (struct net_device*,scalar_t__,struct hns3_enet_coalesce*,struct hns3_enet_coalesce*) ; 
 int /*<<< orphan*/  hns3_nic_dealloc_vector_data (struct hns3_nic_priv*) ; 
 int /*<<< orphan*/  hns3_nic_net_open (struct net_device*) ; 
 int /*<<< orphan*/  hns3_nic_net_stop (struct net_device*) ; 
 int hns3_nic_uninit_vector_data (struct hns3_nic_priv*) ; 
 int /*<<< orphan*/  hns3_put_ring_config (struct hns3_nic_priv*) ; 
 int /*<<< orphan*/  hns3_uninit_all_ring (struct hns3_nic_priv*) ; 
 int /*<<< orphan*/  memcpy (struct hns3_enet_coalesce*,int /*<<< orphan*/ *,int) ; 
 struct hns3_nic_priv* netdev_priv (struct net_device*) ; 
 int netif_running (struct net_device*) ; 

int hns3_set_channels(struct net_device *netdev,
		      struct ethtool_channels *ch)
{
	struct hns3_nic_priv *priv = netdev_priv(netdev);
	struct hnae3_handle *h = hns3_get_handle(netdev);
	struct hnae3_knic_private_info *kinfo = &h->kinfo;
	struct hns3_enet_coalesce tx_coal, rx_coal;
	bool if_running = netif_running(netdev);
	u32 new_tqp_num = ch->combined_count;
	u16 org_tqp_num;
	int ret;

	if (ch->rx_count || ch->tx_count)
		return -EINVAL;

	if (new_tqp_num > hns3_get_max_available_channels(h) ||
	    new_tqp_num < kinfo->num_tc) {
		dev_err(&netdev->dev,
			"Change tqps fail, the tqp range is from %d to %d",
			kinfo->num_tc,
			hns3_get_max_available_channels(h));
		return -EINVAL;
	}

	new_tqp_num = hns3_adjust_tqps_num(kinfo->num_tc, new_tqp_num);
	if (kinfo->num_tqps == new_tqp_num)
		return 0;

	if (if_running)
		hns3_nic_net_stop(netdev);

	ret = hns3_nic_uninit_vector_data(priv);
	if (ret) {
		dev_err(&netdev->dev,
			"Unbind vector with tqp fail, nothing is changed");
		goto open_netdev;
	}

	/* Changing the tqp num may also change the vector num,
	 * ethtool only support setting and querying one coal
	 * configuation for now, so save the vector 0' coal
	 * configuation here in order to restore it.
	 */
	memcpy(&tx_coal, &priv->tqp_vector[0].tx_group.coal,
	       sizeof(struct hns3_enet_coalesce));
	memcpy(&rx_coal, &priv->tqp_vector[0].rx_group.coal,
	       sizeof(struct hns3_enet_coalesce));

	hns3_nic_dealloc_vector_data(priv);

	hns3_uninit_all_ring(priv);
	hns3_put_ring_config(priv);

	org_tqp_num = h->kinfo.num_tqps;
	ret = hns3_modify_tqp_num(netdev, new_tqp_num, &tx_coal, &rx_coal);
	if (ret) {
		ret = hns3_modify_tqp_num(netdev, org_tqp_num,
					  &tx_coal, &rx_coal);
		if (ret) {
			/* If revert to old tqp failed, fatal error occurred */
			dev_err(&netdev->dev,
				"Revert to old tqp num fail, ret=%d", ret);
			return ret;
		}
		dev_info(&netdev->dev,
			 "Change tqp num fail, Revert to old tqp num");
	}

open_netdev:
	if (if_running)
		hns3_nic_net_open(netdev);

	return ret;
}