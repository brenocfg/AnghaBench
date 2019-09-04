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
struct neighbour {int dummy; } ;
struct mlxsw_sp_nexthop {struct mlxsw_sp_neigh_entry* neigh_entry; int /*<<< orphan*/  neigh_list_node; } ;
struct TYPE_2__ {struct neighbour* n; } ;
struct mlxsw_sp_neigh_entry {int /*<<< orphan*/  nexthop_list; int /*<<< orphan*/  connected; int /*<<< orphan*/  nexthop_neighs_list_node; TYPE_1__ key; } ;
struct mlxsw_sp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __mlxsw_sp_nexthop_neigh_update (struct mlxsw_sp_nexthop*,int) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlxsw_sp_neigh_entry_destroy (struct mlxsw_sp*,struct mlxsw_sp_neigh_entry*) ; 
 int /*<<< orphan*/  neigh_release (struct neighbour*) ; 

__attribute__((used)) static void mlxsw_sp_nexthop_neigh_fini(struct mlxsw_sp *mlxsw_sp,
					struct mlxsw_sp_nexthop *nh)
{
	struct mlxsw_sp_neigh_entry *neigh_entry = nh->neigh_entry;
	struct neighbour *n;

	if (!neigh_entry)
		return;
	n = neigh_entry->key.n;

	__mlxsw_sp_nexthop_neigh_update(nh, true);
	list_del(&nh->neigh_list_node);
	nh->neigh_entry = NULL;

	/* If that is the last nexthop connected to that neigh, remove from
	 * nexthop_neighs_list
	 */
	if (list_empty(&neigh_entry->nexthop_list))
		list_del(&neigh_entry->nexthop_neighs_list_node);

	if (!neigh_entry->connected && list_empty(&neigh_entry->nexthop_list))
		mlxsw_sp_neigh_entry_destroy(mlxsw_sp, neigh_entry);

	neigh_release(n);
}