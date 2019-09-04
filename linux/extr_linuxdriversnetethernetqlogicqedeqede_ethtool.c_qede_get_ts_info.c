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
struct qede_dev {int dummy; } ;
struct net_device {int dummy; } ;
struct ethtool_ts_info {int dummy; } ;

/* Variables and functions */
 struct qede_dev* netdev_priv (struct net_device*) ; 
 int qede_ptp_get_ts_info (struct qede_dev*,struct ethtool_ts_info*) ; 

__attribute__((used)) static int qede_get_ts_info(struct net_device *dev,
			    struct ethtool_ts_info *info)
{
	struct qede_dev *edev = netdev_priv(dev);

	return qede_ptp_get_ts_info(edev, info);
}