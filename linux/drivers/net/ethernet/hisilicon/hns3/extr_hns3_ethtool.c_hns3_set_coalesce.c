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
typedef  int u16 ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int num_tqps; int /*<<< orphan*/  int_rl_setting; } ;
struct hnae3_handle {TYPE_1__ kinfo; } ;
struct ethtool_coalesce {int /*<<< orphan*/  rx_coalesce_usecs_high; } ;

/* Variables and functions */
 int EBUSY ; 
 int hns3_check_coalesce_para (struct net_device*,struct ethtool_coalesce*) ; 
 struct hnae3_handle* hns3_get_handle (struct net_device*) ; 
 scalar_t__ hns3_nic_resetting (struct net_device*) ; 
 int /*<<< orphan*/  hns3_rl_round_down (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hns3_set_coalesce_per_queue (struct net_device*,struct ethtool_coalesce*,int) ; 

__attribute__((used)) static int hns3_set_coalesce(struct net_device *netdev,
			     struct ethtool_coalesce *cmd)
{
	struct hnae3_handle *h = hns3_get_handle(netdev);
	u16 queue_num = h->kinfo.num_tqps;
	int ret;
	int i;

	if (hns3_nic_resetting(netdev))
		return -EBUSY;

	ret = hns3_check_coalesce_para(netdev, cmd);
	if (ret)
		return ret;

	h->kinfo.int_rl_setting =
		hns3_rl_round_down(cmd->rx_coalesce_usecs_high);

	for (i = 0; i < queue_num; i++)
		hns3_set_coalesce_per_queue(netdev, cmd, i);

	return 0;
}