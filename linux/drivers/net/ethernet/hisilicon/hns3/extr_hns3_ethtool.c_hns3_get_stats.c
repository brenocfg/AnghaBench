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
typedef  int /*<<< orphan*/  u64 ;
struct net_device {int /*<<< orphan*/  stats; } ;
struct hnae3_handle {TYPE_2__* ae_algo; } ;
struct ethtool_stats {int dummy; } ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* get_stats ) (struct hnae3_handle*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* update_stats ) (struct hnae3_handle*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 struct hnae3_handle* hns3_get_handle (struct net_device*) ; 
 int /*<<< orphan*/ * hns3_get_stats_tqps (struct hnae3_handle*,int /*<<< orphan*/ *) ; 
 scalar_t__ hns3_nic_resetting (struct net_device*) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 int /*<<< orphan*/  stub1 (struct hnae3_handle*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (struct hnae3_handle*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hns3_get_stats(struct net_device *netdev,
			   struct ethtool_stats *stats, u64 *data)
{
	struct hnae3_handle *h = hns3_get_handle(netdev);
	u64 *p = data;

	if (hns3_nic_resetting(netdev)) {
		netdev_err(netdev, "dev resetting, could not get stats\n");
		return;
	}

	if (!h->ae_algo->ops->get_stats || !h->ae_algo->ops->update_stats) {
		netdev_err(netdev, "could not get any statistics\n");
		return;
	}

	h->ae_algo->ops->update_stats(h, &netdev->stats);

	/* get per-queue stats */
	p = hns3_get_stats_tqps(h, p);

	/* get MAC & other misc hardware stats */
	h->ae_algo->ops->get_stats(h, p);
}