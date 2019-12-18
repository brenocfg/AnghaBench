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
struct rmnet_port {scalar_t__ nr_rmnet_devs; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 int /*<<< orphan*/  kfree (struct rmnet_port*) ; 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*) ; 
 int /*<<< orphan*/  netdev_rx_handler_unregister (struct net_device*) ; 

__attribute__((used)) static int rmnet_unregister_real_device(struct net_device *real_dev,
					struct rmnet_port *port)
{
	if (port->nr_rmnet_devs)
		return -EINVAL;

	netdev_rx_handler_unregister(real_dev);

	kfree(port);

	/* release reference on real_dev */
	dev_put(real_dev);

	netdev_dbg(real_dev, "Removed from rmnet\n");
	return 0;
}