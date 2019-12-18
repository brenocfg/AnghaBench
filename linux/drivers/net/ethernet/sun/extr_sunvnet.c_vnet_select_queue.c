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
typedef  int /*<<< orphan*/  u16 ;
struct vnet_port {int /*<<< orphan*/  q_index; } ;
struct vnet {int dummy; } ;
struct sk_buff {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 struct vnet_port* __tx_port_find (struct vnet*,struct sk_buff*) ; 
 struct vnet* netdev_priv (struct net_device*) ; 

__attribute__((used)) static u16 vnet_select_queue(struct net_device *dev, struct sk_buff *skb,
			     struct net_device *sb_dev)
{
	struct vnet *vp = netdev_priv(dev);
	struct vnet_port *port = __tx_port_find(vp, skb);

	if (!port)
		return 0;

	return port->q_index;
}