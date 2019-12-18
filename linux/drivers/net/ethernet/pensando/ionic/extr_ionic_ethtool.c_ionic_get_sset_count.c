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
struct ionic_lif {int dummy; } ;

/* Variables and functions */
#define  ETH_SS_PRIV_FLAGS 129 
#define  ETH_SS_STATS 128 
 int PRIV_FLAGS_COUNT ; 
 int ionic_get_stats_count (struct ionic_lif*) ; 
 struct ionic_lif* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int ionic_get_sset_count(struct net_device *netdev, int sset)
{
	struct ionic_lif *lif = netdev_priv(netdev);
	int count = 0;

	switch (sset) {
	case ETH_SS_STATS:
		count = ionic_get_stats_count(lif);
		break;
	case ETH_SS_PRIV_FLAGS:
		count = PRIV_FLAGS_COUNT;
		break;
	}
	return count;
}