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
struct ethtool_rxnfc {int cmd; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  ETHTOOL_SRXFH 128 
 int dpaa_set_hash_opts (struct net_device*,struct ethtool_rxnfc*) ; 

__attribute__((used)) static int dpaa_set_rxnfc(struct net_device *dev, struct ethtool_rxnfc *cmd)
{
	int ret = -EOPNOTSUPP;

	switch (cmd->cmd) {
	case ETHTOOL_SRXFH:
		ret = dpaa_set_hash_opts(dev, cmd);
		break;
	default:
		break;
	}

	return ret;
}