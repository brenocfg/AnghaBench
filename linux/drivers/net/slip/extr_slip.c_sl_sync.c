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
struct slip {scalar_t__ leased; scalar_t__ tty; } ;
struct net_device {int flags; } ;

/* Variables and functions */
 int IFF_UP ; 
 int /*<<< orphan*/  dev_close (struct net_device*) ; 
 struct slip* netdev_priv (struct net_device*) ; 
 struct net_device** slip_devs ; 
 int slip_maxdev ; 

__attribute__((used)) static void sl_sync(void)
{
	int i;
	struct net_device *dev;
	struct slip	  *sl;

	for (i = 0; i < slip_maxdev; i++) {
		dev = slip_devs[i];
		if (dev == NULL)
			break;

		sl = netdev_priv(dev);
		if (sl->tty || sl->leased)
			continue;
		if (dev->flags & IFF_UP)
			dev_close(dev);
	}
}