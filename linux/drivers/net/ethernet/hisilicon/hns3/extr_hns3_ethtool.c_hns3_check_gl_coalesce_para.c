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
struct ethtool_coalesce {scalar_t__ rx_coalesce_usecs; scalar_t__ tx_coalesce_usecs; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ HNS3_INT_GL_MAX ; 
 scalar_t__ hns3_gl_round_down (scalar_t__) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,scalar_t__) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int hns3_check_gl_coalesce_para(struct net_device *netdev,
				       struct ethtool_coalesce *cmd)
{
	u32 rx_gl, tx_gl;

	if (cmd->rx_coalesce_usecs > HNS3_INT_GL_MAX) {
		netdev_err(netdev,
			   "Invalid rx-usecs value, rx-usecs range is 0-%d\n",
			   HNS3_INT_GL_MAX);
		return -EINVAL;
	}

	if (cmd->tx_coalesce_usecs > HNS3_INT_GL_MAX) {
		netdev_err(netdev,
			   "Invalid tx-usecs value, tx-usecs range is 0-%d\n",
			   HNS3_INT_GL_MAX);
		return -EINVAL;
	}

	rx_gl = hns3_gl_round_down(cmd->rx_coalesce_usecs);
	if (rx_gl != cmd->rx_coalesce_usecs) {
		netdev_info(netdev,
			    "rx_usecs(%d) rounded down to %d, because it must be multiple of 2.\n",
			    cmd->rx_coalesce_usecs, rx_gl);
	}

	tx_gl = hns3_gl_round_down(cmd->tx_coalesce_usecs);
	if (tx_gl != cmd->tx_coalesce_usecs) {
		netdev_info(netdev,
			    "tx_usecs(%d) rounded down to %d, because it must be multiple of 2.\n",
			    cmd->tx_coalesce_usecs, tx_gl);
	}

	return 0;
}