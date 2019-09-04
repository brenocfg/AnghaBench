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

/* Variables and functions */
 int /*<<< orphan*/  dev_close (struct net_device*) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*,int) ; 
 int /*<<< orphan*/  netif_device_attach (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 int sky2_open (struct net_device*) ; 
 int /*<<< orphan*/  sky2_set_multicast (struct net_device*) ; 

__attribute__((used)) static int sky2_reattach(struct net_device *dev)
{
	int err = 0;

	if (netif_running(dev)) {
		err = sky2_open(dev);
		if (err) {
			netdev_info(dev, "could not restart %d\n", err);
			dev_close(dev);
		} else {
			netif_device_attach(dev);
			sky2_set_multicast(dev);
		}
	}

	return err;
}