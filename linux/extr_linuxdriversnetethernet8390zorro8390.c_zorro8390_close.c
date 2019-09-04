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
struct ei_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __ei_close (struct net_device*) ; 
 int /*<<< orphan*/  ifdown ; 
 struct ei_device* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_dbg (struct ei_device*,int /*<<< orphan*/ ,struct net_device*,char*) ; 

__attribute__((used)) static int zorro8390_close(struct net_device *dev)
{
	struct ei_device *ei_local = netdev_priv(dev);

	netif_dbg(ei_local, ifdown, dev, "Shutting down ethercard\n");
	__ei_close(dev);
	return 0;
}