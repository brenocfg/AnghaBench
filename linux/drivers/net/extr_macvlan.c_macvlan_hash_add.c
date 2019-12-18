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
typedef  size_t u32 ;
struct macvlan_port {int /*<<< orphan*/ * vlan_hash; } ;
struct macvlan_dev {int /*<<< orphan*/  hlist; TYPE_1__* dev; struct macvlan_port* port; } ;
struct TYPE_2__ {unsigned char* dev_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  hlist_add_head_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 size_t macvlan_eth_hash (unsigned char const*) ; 

__attribute__((used)) static void macvlan_hash_add(struct macvlan_dev *vlan)
{
	struct macvlan_port *port = vlan->port;
	const unsigned char *addr = vlan->dev->dev_addr;
	u32 idx = macvlan_eth_hash(addr);

	hlist_add_head_rcu(&vlan->hlist, &port->vlan_hash[idx]);
}