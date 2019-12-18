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
struct nicvf {int dummy; } ;
struct net_device {int dummy; } ;
struct ethtool_rxnfc {int cmd; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  ETHTOOL_SRXFH 128 
 struct nicvf* netdev_priv (struct net_device*) ; 
 int nicvf_set_rss_hash_opts (struct nicvf*,struct ethtool_rxnfc*) ; 

__attribute__((used)) static int nicvf_set_rxnfc(struct net_device *dev, struct ethtool_rxnfc *info)
{
	struct nicvf *nic = netdev_priv(dev);

	switch (info->cmd) {
	case ETHTOOL_SRXFH:
		return nicvf_set_rss_hash_opts(nic, info);
	default:
		break;
	}
	return -EOPNOTSUPP;
}