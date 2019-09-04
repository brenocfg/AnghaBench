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
typedef  scalar_t__ u32 ;
struct net_device {int dummy; } ;
struct ethtool_coalesce {scalar_t__ tx_coalesce_usecs_high; scalar_t__ rx_coalesce_usecs_high; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ HNS3_INT_RL_MAX ; 
 scalar_t__ hns3_rl_round_down (scalar_t__) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,...) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int hns3_check_rl_coalesce_para(struct net_device *netdev,
				       struct ethtool_coalesce *cmd)
{
	u32 rl;

	if (cmd->tx_coalesce_usecs_high != cmd->rx_coalesce_usecs_high) {
		netdev_err(netdev,
			   "tx_usecs_high must be same as rx_usecs_high.\n");
		return -EINVAL;
	}

	if (cmd->rx_coalesce_usecs_high > HNS3_INT_RL_MAX) {
		netdev_err(netdev,
			   "Invalid usecs_high value, usecs_high range is 0-%d\n",
			   HNS3_INT_RL_MAX);
		return -EINVAL;
	}

	rl = hns3_rl_round_down(cmd->rx_coalesce_usecs_high);
	if (rl != cmd->rx_coalesce_usecs_high) {
		netdev_info(netdev,
			    "usecs_high(%d) rounded down to %d, because it must be multiple of 4.\n",
			    cmd->rx_coalesce_usecs_high, rl);
	}

	return 0;
}