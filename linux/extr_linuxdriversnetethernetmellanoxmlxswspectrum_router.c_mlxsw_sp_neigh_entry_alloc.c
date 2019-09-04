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
typedef  int /*<<< orphan*/  u16 ;
struct neighbour {int dummy; } ;
struct TYPE_2__ {struct neighbour* n; } ;
struct mlxsw_sp_neigh_entry {int /*<<< orphan*/  nexthop_list; int /*<<< orphan*/  rif; TYPE_1__ key; } ;
struct mlxsw_sp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct mlxsw_sp_neigh_entry* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct mlxsw_sp_neigh_entry *
mlxsw_sp_neigh_entry_alloc(struct mlxsw_sp *mlxsw_sp, struct neighbour *n,
			   u16 rif)
{
	struct mlxsw_sp_neigh_entry *neigh_entry;

	neigh_entry = kzalloc(sizeof(*neigh_entry), GFP_KERNEL);
	if (!neigh_entry)
		return NULL;

	neigh_entry->key.n = n;
	neigh_entry->rif = rif;
	INIT_LIST_HEAD(&neigh_entry->nexthop_list);

	return neigh_entry;
}