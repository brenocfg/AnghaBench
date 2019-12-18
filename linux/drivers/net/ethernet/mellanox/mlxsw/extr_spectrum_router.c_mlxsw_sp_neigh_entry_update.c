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
struct TYPE_6__ {TYPE_2__* n; } ;
struct mlxsw_sp_neigh_entry {int connected; TYPE_3__ key; } ;
struct mlxsw_sp {int dummy; } ;
typedef  enum mlxsw_reg_rauht_op { ____Placeholder_mlxsw_reg_rauht_op } mlxsw_reg_rauht_op ;
struct TYPE_5__ {int /*<<< orphan*/  flags; TYPE_1__* tbl; } ;
struct TYPE_4__ {scalar_t__ family; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 int /*<<< orphan*/  NTF_OFFLOADED ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 scalar_t__ mlxsw_sp_neigh_ipv6_ignore (struct mlxsw_sp_neigh_entry*) ; 
 int mlxsw_sp_rauht_op (int) ; 
 int mlxsw_sp_router_neigh_entry_op4 (struct mlxsw_sp*,struct mlxsw_sp_neigh_entry*,int) ; 
 int mlxsw_sp_router_neigh_entry_op6 (struct mlxsw_sp*,struct mlxsw_sp_neigh_entry*,int) ; 

__attribute__((used)) static void
mlxsw_sp_neigh_entry_update(struct mlxsw_sp *mlxsw_sp,
			    struct mlxsw_sp_neigh_entry *neigh_entry,
			    bool adding)
{
	enum mlxsw_reg_rauht_op op = mlxsw_sp_rauht_op(adding);
	int err;

	if (!adding && !neigh_entry->connected)
		return;
	neigh_entry->connected = adding;
	if (neigh_entry->key.n->tbl->family == AF_INET) {
		err = mlxsw_sp_router_neigh_entry_op4(mlxsw_sp, neigh_entry,
						      op);
		if (err)
			return;
	} else if (neigh_entry->key.n->tbl->family == AF_INET6) {
		if (mlxsw_sp_neigh_ipv6_ignore(neigh_entry))
			return;
		err = mlxsw_sp_router_neigh_entry_op6(mlxsw_sp, neigh_entry,
						      op);
		if (err)
			return;
	} else {
		WARN_ON_ONCE(1);
		return;
	}

	if (adding)
		neigh_entry->key.n->flags |= NTF_OFFLOADED;
	else
		neigh_entry->key.n->flags &= ~NTF_OFFLOADED;
}