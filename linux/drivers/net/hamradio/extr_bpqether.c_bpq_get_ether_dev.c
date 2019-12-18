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
struct bpqdev {struct net_device* ethdev; } ;

/* Variables and functions */
 struct bpqdev* netdev_priv (struct net_device*) ; 

__attribute__((used)) static inline struct net_device *bpq_get_ether_dev(struct net_device *dev)
{
	struct bpqdev *bpq = netdev_priv(dev);

	return bpq ? bpq->ethdev : NULL;
}