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

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  ETH_SS_STATS 128 
 int MLXSW_SP_PORT_ETHTOOL_STATS_LEN ; 

__attribute__((used)) static int mlxsw_sp_port_get_sset_count(struct net_device *dev, int sset)
{
	switch (sset) {
	case ETH_SS_STATS:
		return MLXSW_SP_PORT_ETHTOOL_STATS_LEN;
	default:
		return -EOPNOTSUPP;
	}
}