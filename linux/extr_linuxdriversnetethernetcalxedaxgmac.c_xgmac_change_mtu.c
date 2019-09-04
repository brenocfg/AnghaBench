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
struct net_device {int mtu; } ;

/* Variables and functions */
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 int xgmac_open (struct net_device*) ; 
 int /*<<< orphan*/  xgmac_stop (struct net_device*) ; 

__attribute__((used)) static int xgmac_change_mtu(struct net_device *dev, int new_mtu)
{
	/* Stop everything, get ready to change the MTU */
	if (!netif_running(dev))
		return 0;

	/* Bring interface down, change mtu and bring interface back up */
	xgmac_stop(dev);
	dev->mtu = new_mtu;
	return xgmac_open(dev);
}