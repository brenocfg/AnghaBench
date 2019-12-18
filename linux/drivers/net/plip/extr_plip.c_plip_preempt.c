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
struct net_local {scalar_t__ connection; int should_relinquish; scalar_t__ port_owner; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ PLIP_CN_NONE ; 
 struct net_local* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int
plip_preempt(void *handle)
{
	struct net_device *dev = (struct net_device *)handle;
	struct net_local *nl = netdev_priv(dev);

	/* Stand our ground if a datagram is on the wire */
	if (nl->connection != PLIP_CN_NONE) {
		nl->should_relinquish = 1;
		return 1;
	}

	nl->port_owner = 0;	/* Remember that we released the bus */
	return 0;
}