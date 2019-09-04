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
struct net_device {int dummy; } ;
struct macb {TYPE_1__* ptp_info; } ;
struct ethtool_ts_info {int dummy; } ;
struct TYPE_2__ {int (* get_ts_info ) (struct net_device*,struct ethtool_ts_info*) ;} ;

/* Variables and functions */
 int ethtool_op_get_ts_info (struct net_device*,struct ethtool_ts_info*) ; 
 struct macb* netdev_priv (struct net_device*) ; 
 int stub1 (struct net_device*,struct ethtool_ts_info*) ; 

__attribute__((used)) static int macb_get_ts_info(struct net_device *netdev,
			    struct ethtool_ts_info *info)
{
	struct macb *bp = netdev_priv(netdev);

	if (bp->ptp_info)
		return bp->ptp_info->get_ts_info(netdev, info);

	return ethtool_op_get_ts_info(netdev, info);
}