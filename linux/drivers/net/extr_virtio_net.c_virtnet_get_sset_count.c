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
struct virtnet_info {int curr_queue_pairs; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  ETH_SS_STATS 128 
 int VIRTNET_RQ_STATS_LEN ; 
 int VIRTNET_SQ_STATS_LEN ; 
 struct virtnet_info* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int virtnet_get_sset_count(struct net_device *dev, int sset)
{
	struct virtnet_info *vi = netdev_priv(dev);

	switch (sset) {
	case ETH_SS_STATS:
		return vi->curr_queue_pairs * (VIRTNET_RQ_STATS_LEN +
					       VIRTNET_SQ_STATS_LEN);
	default:
		return -EOPNOTSUPP;
	}
}