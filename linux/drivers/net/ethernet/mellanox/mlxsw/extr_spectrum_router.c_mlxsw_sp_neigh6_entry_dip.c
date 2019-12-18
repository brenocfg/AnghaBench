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

struct in6_addr *
mlxsw_sp_neigh6_entry_dip(struct mlxsw_sp_neigh_entry *neigh_entry)
{
	struct neighbour *n;

	n = neigh_entry->key.n;
	return (struct in6_addr *) &n->primary_key;
}