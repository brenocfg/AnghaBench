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
struct neighbour {int /*<<< orphan*/  primary_key; } ;
struct TYPE_2__ {struct neighbour* n; } ;
struct mlxsw_sp_neigh_entry {TYPE_1__ key; } ;
struct in6_addr {int dummy; } ;

/* Variables and functions */
 int IPV6_ADDR_LINKLOCAL ; 
 int ipv6_addr_type (struct in6_addr*) ; 

bool mlxsw_sp_neigh_ipv6_ignore(struct mlxsw_sp_neigh_entry *neigh_entry)
{
	struct neighbour *n = neigh_entry->key.n;

	/* Packets with a link-local destination address are trapped
	 * after LPM lookup and never reach the neighbour table, so
	 * there is no need to program such neighbours to the device.
	 */
	if (ipv6_addr_type((struct in6_addr *) &n->primary_key) &
	    IPV6_ADDR_LINKLOCAL)
		return true;
	return false;
}