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
struct timer_list {int dummy; } ;
struct net_device {int dummy; } ;
struct arcnet_local {struct net_device* dev; } ;

/* Variables and functions */
 struct arcnet_local* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 struct arcnet_local* lp ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*) ; 
 int /*<<< orphan*/  netif_carrier_ok (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_on (struct net_device*) ; 
 int /*<<< orphan*/  timer ; 

__attribute__((used)) static void arcnet_timer(struct timer_list *t)
{
	struct arcnet_local *lp = from_timer(lp, t, timer);
	struct net_device *dev = lp->dev;

	if (!netif_carrier_ok(dev)) {
		netif_carrier_on(dev);
		netdev_info(dev, "link up\n");
	}
}