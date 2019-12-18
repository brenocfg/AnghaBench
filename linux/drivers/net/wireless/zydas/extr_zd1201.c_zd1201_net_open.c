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
struct zd1201 {int /*<<< orphan*/  essidlen; int /*<<< orphan*/  essid; int /*<<< orphan*/  mac_enabled; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 struct zd1201* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int /*<<< orphan*/  zd1201_join (struct zd1201*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int zd1201_net_open(struct net_device *dev)
{
	struct zd1201 *zd = netdev_priv(dev);

	/* Start MAC with wildcard if no essid set */
	if (!zd->mac_enabled)
		zd1201_join(zd, zd->essid, zd->essidlen);
	netif_start_queue(dev);

	return 0;
}