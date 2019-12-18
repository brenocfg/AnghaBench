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
typedef  int u32 ;
typedef  int u16 ;
struct net_device {int /*<<< orphan*/  dev; } ;
struct hnae3_knic_private_info {int rss_size; int num_tqps; } ;
struct hnae3_handle {struct hnae3_knic_private_info kinfo; } ;
struct ethtool_channels {int combined_count; scalar_t__ tx_count; scalar_t__ rx_count; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  HNAE3_DOWN_CLIENT ; 
 int /*<<< orphan*/  HNAE3_UNINIT_CLIENT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  drv ; 
 int hns3_change_channels (struct hnae3_handle*,int,int) ; 
 struct hnae3_handle* hns3_get_handle (struct net_device*) ; 
 int hns3_get_max_available_channels (struct hnae3_handle*) ; 
 scalar_t__ hns3_nic_resetting (struct net_device*) ; 
 int hns3_reset_notify (struct hnae3_handle*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 int /*<<< orphan*/  netdev_warn (struct net_device*,char*) ; 
 int /*<<< orphan*/  netif_dbg (struct hnae3_handle*,int /*<<< orphan*/ ,struct net_device*,char*,int,int) ; 
 int netif_is_rxfh_configured (struct net_device*) ; 

int hns3_set_channels(struct net_device *netdev,
		      struct ethtool_channels *ch)
{
	struct hnae3_handle *h = hns3_get_handle(netdev);
	struct hnae3_knic_private_info *kinfo = &h->kinfo;
	bool rxfh_configured = netif_is_rxfh_configured(netdev);
	u32 new_tqp_num = ch->combined_count;
	u16 org_tqp_num;
	int ret;

	if (hns3_nic_resetting(netdev))
		return -EBUSY;

	if (ch->rx_count || ch->tx_count)
		return -EINVAL;

	if (new_tqp_num > hns3_get_max_available_channels(h) ||
	    new_tqp_num < 1) {
		dev_err(&netdev->dev,
			"Change tqps fail, the tqp range is from 1 to %d",
			hns3_get_max_available_channels(h));
		return -EINVAL;
	}

	if (kinfo->rss_size == new_tqp_num)
		return 0;

	netif_dbg(h, drv, netdev,
		  "set channels: tqp_num=%u, rxfh=%d\n",
		  new_tqp_num, rxfh_configured);

	ret = hns3_reset_notify(h, HNAE3_DOWN_CLIENT);
	if (ret)
		return ret;

	ret = hns3_reset_notify(h, HNAE3_UNINIT_CLIENT);
	if (ret)
		return ret;

	org_tqp_num = h->kinfo.num_tqps;
	ret = hns3_change_channels(h, new_tqp_num, rxfh_configured);
	if (ret) {
		int ret1;

		netdev_warn(netdev,
			    "Change channels fail, revert to old value\n");
		ret1 = hns3_change_channels(h, org_tqp_num, rxfh_configured);
		if (ret1) {
			netdev_err(netdev,
				   "revert to old channel fail\n");
			return ret1;
		}

		return ret;
	}

	return 0;
}