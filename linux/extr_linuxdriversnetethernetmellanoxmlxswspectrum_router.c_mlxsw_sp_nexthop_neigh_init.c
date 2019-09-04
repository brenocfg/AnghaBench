#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct neighbour {int nud_state; int dead; int /*<<< orphan*/  lock; int /*<<< orphan*/  nexthop_list; int /*<<< orphan*/  nexthop_neighs_list_node; } ;
struct mlxsw_sp_nexthop {int /*<<< orphan*/  neigh_list_node; struct neighbour* neigh_entry; TYPE_2__* rif; int /*<<< orphan*/  gw_addr; TYPE_1__* nh_grp; } ;
struct mlxsw_sp_neigh_entry {int nud_state; int dead; int /*<<< orphan*/  lock; int /*<<< orphan*/  nexthop_list; int /*<<< orphan*/  nexthop_neighs_list_node; } ;
struct mlxsw_sp {TYPE_3__* router; } ;
struct TYPE_6__ {int /*<<< orphan*/  nexthop_neighs_list; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  neigh_tbl; int /*<<< orphan*/  gateway; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (struct neighbour*) ; 
 int NUD_VALID ; 
 int PTR_ERR (struct neighbour*) ; 
 int /*<<< orphan*/  __mlxsw_sp_nexthop_neigh_update (struct mlxsw_sp_nexthop*,int) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 struct neighbour* mlxsw_sp_neigh_entry_create (struct mlxsw_sp*,struct neighbour*) ; 
 struct neighbour* mlxsw_sp_neigh_entry_lookup (struct mlxsw_sp*,struct neighbour*) ; 
 struct neighbour* neigh_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  neigh_event_send (struct neighbour*,int /*<<< orphan*/ *) ; 
 struct neighbour* neigh_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  neigh_release (struct neighbour*) ; 
 int /*<<< orphan*/  read_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mlxsw_sp_nexthop_neigh_init(struct mlxsw_sp *mlxsw_sp,
				       struct mlxsw_sp_nexthop *nh)
{
	struct mlxsw_sp_neigh_entry *neigh_entry;
	struct neighbour *n;
	u8 nud_state, dead;
	int err;

	if (!nh->nh_grp->gateway || nh->neigh_entry)
		return 0;

	/* Take a reference of neigh here ensuring that neigh would
	 * not be destructed before the nexthop entry is finished.
	 * The reference is taken either in neigh_lookup() or
	 * in neigh_create() in case n is not found.
	 */
	n = neigh_lookup(nh->nh_grp->neigh_tbl, &nh->gw_addr, nh->rif->dev);
	if (!n) {
		n = neigh_create(nh->nh_grp->neigh_tbl, &nh->gw_addr,
				 nh->rif->dev);
		if (IS_ERR(n))
			return PTR_ERR(n);
		neigh_event_send(n, NULL);
	}
	neigh_entry = mlxsw_sp_neigh_entry_lookup(mlxsw_sp, n);
	if (!neigh_entry) {
		neigh_entry = mlxsw_sp_neigh_entry_create(mlxsw_sp, n);
		if (IS_ERR(neigh_entry)) {
			err = -EINVAL;
			goto err_neigh_entry_create;
		}
	}

	/* If that is the first nexthop connected to that neigh, add to
	 * nexthop_neighs_list
	 */
	if (list_empty(&neigh_entry->nexthop_list))
		list_add_tail(&neigh_entry->nexthop_neighs_list_node,
			      &mlxsw_sp->router->nexthop_neighs_list);

	nh->neigh_entry = neigh_entry;
	list_add_tail(&nh->neigh_list_node, &neigh_entry->nexthop_list);
	read_lock_bh(&n->lock);
	nud_state = n->nud_state;
	dead = n->dead;
	read_unlock_bh(&n->lock);
	__mlxsw_sp_nexthop_neigh_update(nh, !(nud_state & NUD_VALID && !dead));

	return 0;

err_neigh_entry_create:
	neigh_release(n);
	return err;
}