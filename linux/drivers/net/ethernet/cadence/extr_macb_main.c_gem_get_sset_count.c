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
struct macb {int num_queues; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  ETH_SS_STATS 128 
 int GEM_STATS_LEN ; 
 int QUEUE_STATS_LEN ; 
 struct macb* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int gem_get_sset_count(struct net_device *dev, int sset)
{
	struct macb *bp = netdev_priv(dev);

	switch (sset) {
	case ETH_SS_STATS:
		return GEM_STATS_LEN + bp->num_queues * QUEUE_STATS_LEN;
	default:
		return -EOPNOTSUPP;
	}
}