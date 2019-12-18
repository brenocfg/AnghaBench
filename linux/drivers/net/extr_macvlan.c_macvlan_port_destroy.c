#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sockaddr {int /*<<< orphan*/  sa_data; int /*<<< orphan*/  sa_family; } ;
struct sk_buff {int dummy; } ;
struct net_device {int /*<<< orphan*/  priv_flags; } ;
struct macvlan_port {TYPE_1__* dev; int /*<<< orphan*/  perm_addr; int /*<<< orphan*/  bc_queue; int /*<<< orphan*/  bc_work; } ;
struct macvlan_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {struct macvlan_dev* src; } ;
struct TYPE_3__ {int /*<<< orphan*/  addr_len; int /*<<< orphan*/  type; int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFF_MACVLAN_PORT ; 
 TYPE_2__* MACVLAN_SKB_CB (struct sk_buff*) ; 
 struct sk_buff* __skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_set_mac_address (TYPE_1__*,struct sockaddr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ether_addr_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct macvlan_port*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 scalar_t__ macvlan_passthru (struct macvlan_port*) ; 
 struct macvlan_port* macvlan_port_get_rtnl (struct net_device*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_rx_handler_unregister (struct net_device*) ; 

__attribute__((used)) static void macvlan_port_destroy(struct net_device *dev)
{
	struct macvlan_port *port = macvlan_port_get_rtnl(dev);
	struct sk_buff *skb;

	dev->priv_flags &= ~IFF_MACVLAN_PORT;
	netdev_rx_handler_unregister(dev);

	/* After this point, no packet can schedule bc_work anymore,
	 * but we need to cancel it and purge left skbs if any.
	 */
	cancel_work_sync(&port->bc_work);

	while ((skb = __skb_dequeue(&port->bc_queue))) {
		const struct macvlan_dev *src = MACVLAN_SKB_CB(skb)->src;

		if (src)
			dev_put(src->dev);

		kfree_skb(skb);
	}

	/* If the lower device address has been changed by passthru
	 * macvlan, put it back.
	 */
	if (macvlan_passthru(port) &&
	    !ether_addr_equal(port->dev->dev_addr, port->perm_addr)) {
		struct sockaddr sa;

		sa.sa_family = port->dev->type;
		memcpy(&sa.sa_data, port->perm_addr, port->dev->addr_len);
		dev_set_mac_address(port->dev, &sa, NULL);
	}

	kfree(port);
}