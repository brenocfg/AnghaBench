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
typedef  size_t u8 ;
struct ipvl_port {int /*<<< orphan*/ * hlhead; } ;
struct ipvl_dev {struct ipvl_port* port; } ;
struct ipvl_addr {scalar_t__ atype; int /*<<< orphan*/  hlnode; int /*<<< orphan*/  ip4addr; int /*<<< orphan*/  ip6addr; } ;

/* Variables and functions */
 scalar_t__ IPVL_IPV6 ; 
 int /*<<< orphan*/  hlist_add_head_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ hlist_unhashed (int /*<<< orphan*/ *) ; 
 size_t ipvlan_get_v4_hash (int /*<<< orphan*/ *) ; 
 size_t ipvlan_get_v6_hash (int /*<<< orphan*/ *) ; 

void ipvlan_ht_addr_add(struct ipvl_dev *ipvlan, struct ipvl_addr *addr)
{
	struct ipvl_port *port = ipvlan->port;
	u8 hash;

	hash = (addr->atype == IPVL_IPV6) ?
	       ipvlan_get_v6_hash(&addr->ip6addr) :
	       ipvlan_get_v4_hash(&addr->ip4addr);
	if (hlist_unhashed(&addr->hlnode))
		hlist_add_head_rcu(&addr->hlnode, &port->hlhead[hash]);
}