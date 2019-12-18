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
struct net_vrf {int dummy; } ;
struct net_device {int /*<<< orphan*/ * dstats; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_percpu (int /*<<< orphan*/ *) ; 
 struct net_vrf* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  vrf_rt6_release (struct net_device*,struct net_vrf*) ; 
 int /*<<< orphan*/  vrf_rtable_release (struct net_device*,struct net_vrf*) ; 

__attribute__((used)) static void vrf_dev_uninit(struct net_device *dev)
{
	struct net_vrf *vrf = netdev_priv(dev);

	vrf_rtable_release(dev, vrf);
	vrf_rt6_release(dev, vrf);

	free_percpu(dev->dstats);
	dev->dstats = NULL;
}