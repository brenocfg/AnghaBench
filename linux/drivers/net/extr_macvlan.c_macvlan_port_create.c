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
struct net_device {scalar_t__ type; int flags; int /*<<< orphan*/  priv_flags; int /*<<< orphan*/  dev_addr; } ;
struct macvlan_port {int /*<<< orphan*/  bc_work; int /*<<< orphan*/  bc_queue; int /*<<< orphan*/ * vlan_source_hash; int /*<<< orphan*/ * vlan_hash; int /*<<< orphan*/  vlans; int /*<<< orphan*/  perm_addr; struct net_device* dev; } ;

/* Variables and functions */
 scalar_t__ ARPHRD_ETHER ; 
 int EBUSY ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IFF_LOOPBACK ; 
 int /*<<< orphan*/  IFF_MACVLAN_PORT ; 
 int /*<<< orphan*/  INIT_HLIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 unsigned int MACVLAN_HASH_SIZE ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct macvlan_port*) ; 
 struct macvlan_port* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  macvlan_handle_frame ; 
 int /*<<< orphan*/  macvlan_process_broadcast ; 
 scalar_t__ netdev_is_rx_handler_busy (struct net_device*) ; 
 int netdev_rx_handler_register (struct net_device*,int /*<<< orphan*/ ,struct macvlan_port*) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int macvlan_port_create(struct net_device *dev)
{
	struct macvlan_port *port;
	unsigned int i;
	int err;

	if (dev->type != ARPHRD_ETHER || dev->flags & IFF_LOOPBACK)
		return -EINVAL;

	if (netdev_is_rx_handler_busy(dev))
		return -EBUSY;

	port = kzalloc(sizeof(*port), GFP_KERNEL);
	if (port == NULL)
		return -ENOMEM;

	port->dev = dev;
	ether_addr_copy(port->perm_addr, dev->dev_addr);
	INIT_LIST_HEAD(&port->vlans);
	for (i = 0; i < MACVLAN_HASH_SIZE; i++)
		INIT_HLIST_HEAD(&port->vlan_hash[i]);
	for (i = 0; i < MACVLAN_HASH_SIZE; i++)
		INIT_HLIST_HEAD(&port->vlan_source_hash[i]);

	skb_queue_head_init(&port->bc_queue);
	INIT_WORK(&port->bc_work, macvlan_process_broadcast);

	err = netdev_rx_handler_register(dev, macvlan_handle_frame, port);
	if (err)
		kfree(port);
	else
		dev->priv_flags |= IFF_MACVLAN_PORT;
	return err;
}