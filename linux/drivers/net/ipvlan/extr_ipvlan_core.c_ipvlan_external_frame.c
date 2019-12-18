#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {TYPE_1__* dev; } ;
struct ipvl_port {int dummy; } ;
struct ipvl_addr {int dummy; } ;
struct ethhdr {int /*<<< orphan*/  h_source; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 struct ethhdr* eth_hdr (struct sk_buff*) ; 
 scalar_t__ ether_addr_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ipvl_addr* ipvlan_addr_lookup (struct ipvl_port*,void*,int,int) ; 
 void* ipvlan_get_L3_hdr (struct ipvl_port*,struct sk_buff*,int*) ; 

__attribute__((used)) static bool ipvlan_external_frame(struct sk_buff *skb, struct ipvl_port *port)
{
	struct ethhdr *eth = eth_hdr(skb);
	struct ipvl_addr *addr;
	void *lyr3h;
	int addr_type;

	if (ether_addr_equal(eth->h_source, skb->dev->dev_addr)) {
		lyr3h = ipvlan_get_L3_hdr(port, skb, &addr_type);
		if (!lyr3h)
			return true;

		addr = ipvlan_addr_lookup(port, lyr3h, addr_type, false);
		if (addr)
			return false;
	}

	return true;
}