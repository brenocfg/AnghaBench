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
typedef  scalar_t__ u64 ;
struct virtnet_info {scalar_t__ guest_offloads; scalar_t__ guest_offloads_capable; scalar_t__ xdp_queue_pairs; } ;
struct net_device {int features; } ;
typedef  int netdev_features_t ;

/* Variables and functions */
 int EBUSY ; 
 int NETIF_F_LRO ; 
 struct virtnet_info* netdev_priv (struct net_device*) ; 
 int virtnet_set_guest_offloads (struct virtnet_info*,scalar_t__) ; 

__attribute__((used)) static int virtnet_set_features(struct net_device *dev,
				netdev_features_t features)
{
	struct virtnet_info *vi = netdev_priv(dev);
	u64 offloads;
	int err;

	if ((dev->features ^ features) & NETIF_F_LRO) {
		if (vi->xdp_queue_pairs)
			return -EBUSY;

		if (features & NETIF_F_LRO)
			offloads = vi->guest_offloads_capable;
		else
			offloads = 0;

		err = virtnet_set_guest_offloads(vi, offloads);
		if (err)
			return err;
		vi->guest_offloads = offloads;
	}

	return 0;
}