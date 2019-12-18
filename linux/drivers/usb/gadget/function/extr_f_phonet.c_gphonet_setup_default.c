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
struct phonet_port {int /*<<< orphan*/  lock; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct net_device* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NET_NAME_UNKNOWN ; 
 struct net_device* alloc_netdev (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct phonet_port* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  pn_net_setup ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

struct net_device *gphonet_setup_default(void)
{
	struct net_device *dev;
	struct phonet_port *port;

	/* Create net device */
	dev = alloc_netdev(sizeof(*port), "upnlink%d", NET_NAME_UNKNOWN,
			   pn_net_setup);
	if (!dev)
		return ERR_PTR(-ENOMEM);

	port = netdev_priv(dev);
	spin_lock_init(&port->lock);
	netif_carrier_off(dev);

	return dev;
}