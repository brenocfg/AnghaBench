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
struct ipvl_port {int dev_id_start; int /*<<< orphan*/  ida; int /*<<< orphan*/  wq; int /*<<< orphan*/  backlog; int /*<<< orphan*/ * hlhead; int /*<<< orphan*/  ipvlans; int /*<<< orphan*/  mode; struct net_device* dev; int /*<<< orphan*/  pnet; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_HLIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int IPVLAN_HASH_SIZE ; 
 int /*<<< orphan*/  IPVLAN_MODE_L3 ; 
 int /*<<< orphan*/  dev_net (struct net_device*) ; 
 int /*<<< orphan*/  ida_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipvlan_handle_frame ; 
 int /*<<< orphan*/  ipvlan_process_multicast ; 
 int /*<<< orphan*/  kfree (struct ipvl_port*) ; 
 struct ipvl_port* kzalloc (int,int /*<<< orphan*/ ) ; 
 int netdev_rx_handler_register (struct net_device*,int /*<<< orphan*/ ,struct ipvl_port*) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_pnet (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ipvlan_port_create(struct net_device *dev)
{
	struct ipvl_port *port;
	int err, idx;

	port = kzalloc(sizeof(struct ipvl_port), GFP_KERNEL);
	if (!port)
		return -ENOMEM;

	write_pnet(&port->pnet, dev_net(dev));
	port->dev = dev;
	port->mode = IPVLAN_MODE_L3;
	INIT_LIST_HEAD(&port->ipvlans);
	for (idx = 0; idx < IPVLAN_HASH_SIZE; idx++)
		INIT_HLIST_HEAD(&port->hlhead[idx]);

	skb_queue_head_init(&port->backlog);
	INIT_WORK(&port->wq, ipvlan_process_multicast);
	ida_init(&port->ida);
	port->dev_id_start = 1;

	err = netdev_rx_handler_register(dev, ipvlan_handle_frame, port);
	if (err)
		goto err;

	return 0;

err:
	kfree(port);
	return err;
}