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
struct sk_buff {int dummy; } ;
struct net_device {int dummy; } ;
struct ipvl_port {scalar_t__ mode; } ;
struct ipvl_addr {int dummy; } ;

/* Variables and functions */
 scalar_t__ IPVLAN_MODE_L3S ; 
 struct ipvl_addr* ipvlan_addr_lookup (struct ipvl_port*,void*,int,int) ; 
 void* ipvlan_get_L3_hdr (struct ipvl_port*,struct sk_buff*,int*) ; 
 struct ipvl_port* ipvlan_port_get_rcu (struct net_device*) ; 
 int /*<<< orphan*/  netif_is_ipvlan_port (struct net_device*) ; 

__attribute__((used)) static struct ipvl_addr *ipvlan_skb_to_addr(struct sk_buff *skb,
					    struct net_device *dev)
{
	struct ipvl_addr *addr = NULL;
	struct ipvl_port *port;
	int addr_type;
	void *lyr3h;

	if (!dev || !netif_is_ipvlan_port(dev))
		goto out;

	port = ipvlan_port_get_rcu(dev);
	if (!port || port->mode != IPVLAN_MODE_L3S)
		goto out;

	lyr3h = ipvlan_get_L3_hdr(port, skb, &addr_type);
	if (!lyr3h)
		goto out;

	addr = ipvlan_addr_lookup(port, lyr3h, addr_type, true);
out:
	return addr;
}