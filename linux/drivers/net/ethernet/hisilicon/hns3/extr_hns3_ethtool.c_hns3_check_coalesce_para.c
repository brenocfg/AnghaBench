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
struct net_device {int dummy; } ;
struct ethtool_coalesce {int use_adaptive_tx_coalesce; int use_adaptive_rx_coalesce; } ;

/* Variables and functions */
 int hns3_check_gl_coalesce_para (struct net_device*,struct ethtool_coalesce*) ; 
 int hns3_check_rl_coalesce_para (struct net_device*,struct ethtool_coalesce*) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,int) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*,int,int) ; 

__attribute__((used)) static int hns3_check_coalesce_para(struct net_device *netdev,
				    struct ethtool_coalesce *cmd)
{
	int ret;

	ret = hns3_check_gl_coalesce_para(netdev, cmd);
	if (ret) {
		netdev_err(netdev,
			   "Check gl coalesce param fail. ret = %d\n", ret);
		return ret;
	}

	ret = hns3_check_rl_coalesce_para(netdev, cmd);
	if (ret) {
		netdev_err(netdev,
			   "Check rl coalesce param fail. ret = %d\n", ret);
		return ret;
	}

	if (cmd->use_adaptive_tx_coalesce == 1 ||
	    cmd->use_adaptive_rx_coalesce == 1) {
		netdev_info(netdev,
			    "adaptive-tx=%d and adaptive-rx=%d, tx_usecs or rx_usecs will changed dynamically.\n",
			    cmd->use_adaptive_tx_coalesce,
			    cmd->use_adaptive_rx_coalesce);
	}

	return 0;
}