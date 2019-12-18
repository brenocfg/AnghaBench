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
struct net_device {int /*<<< orphan*/  dev_addr; } ;
struct enc28j60_net {int dummy; } ;

/* Variables and functions */
 int EADDRNOTAVAIL ; 
 int EINVAL ; 
 int /*<<< orphan*/  enc28j60_check_link_status (struct net_device*) ; 
 int /*<<< orphan*/  enc28j60_hw_disable (struct enc28j60_net*) ; 
 int /*<<< orphan*/  enc28j60_hw_enable (struct enc28j60_net*) ; 
 int /*<<< orphan*/  enc28j60_hw_init (struct enc28j60_net*) ; 
 int /*<<< orphan*/  enc28j60_lowpower (struct enc28j60_net*,int) ; 
 int /*<<< orphan*/  enc28j60_set_hw_macaddr (struct net_device*) ; 
 int /*<<< orphan*/  is_valid_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,...) ; 
 struct enc28j60_net* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_msg_ifup (struct enc28j60_net*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 

__attribute__((used)) static int enc28j60_net_open(struct net_device *dev)
{
	struct enc28j60_net *priv = netdev_priv(dev);

	if (!is_valid_ether_addr(dev->dev_addr)) {
		if (netif_msg_ifup(priv))
			netdev_err(dev, "invalid MAC address %pM\n", dev->dev_addr);
		return -EADDRNOTAVAIL;
	}
	/* Reset the hardware here (and take it out of low power mode) */
	enc28j60_lowpower(priv, false);
	enc28j60_hw_disable(priv);
	if (!enc28j60_hw_init(priv)) {
		if (netif_msg_ifup(priv))
			netdev_err(dev, "hw_reset() failed\n");
		return -EINVAL;
	}
	/* Update the MAC address (in case user has changed it) */
	enc28j60_set_hw_macaddr(dev);
	/* Enable interrupts */
	enc28j60_hw_enable(priv);
	/* check link status */
	enc28j60_check_link_status(dev);
	/* We are now ready to accept transmit requests from
	 * the queueing layer of the networking.
	 */
	netif_start_queue(dev);

	return 0;
}