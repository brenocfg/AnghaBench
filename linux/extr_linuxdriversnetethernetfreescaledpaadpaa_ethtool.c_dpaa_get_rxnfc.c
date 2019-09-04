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
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int dummy; } ;
struct ethtool_rxnfc {int cmd; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  ETHTOOL_GRXFH 128 
 int dpaa_get_hash_opts (struct net_device*,struct ethtool_rxnfc*) ; 

__attribute__((used)) static int dpaa_get_rxnfc(struct net_device *dev, struct ethtool_rxnfc *cmd,
			  u32 *unused)
{
	int ret = -EOPNOTSUPP;

	switch (cmd->cmd) {
	case ETHTOOL_GRXFH:
		ret = dpaa_get_hash_opts(dev, cmd);
		break;
	default:
		break;
	}

	return ret;
}