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
 int EINVAL ; 
 int EMAC_ETHTOOL_STATS_COUNT ; 
 int ETH_SS_STATS ; 

__attribute__((used)) static int emac_ethtool_get_sset_count(struct net_device *ndev, int stringset)
{
	if (stringset == ETH_SS_STATS)
		return EMAC_ETHTOOL_STATS_COUNT;
	else
		return -EINVAL;
}