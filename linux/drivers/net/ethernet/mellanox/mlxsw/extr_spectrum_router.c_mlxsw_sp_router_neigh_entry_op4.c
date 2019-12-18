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
typedef  int /*<<< orphan*/  u32 ;
struct neighbour {scalar_t__ primary_key; } ;
struct TYPE_2__ {struct neighbour* n; } ;
struct mlxsw_sp_neigh_entry {int /*<<< orphan*/  counter_index; scalar_t__ counter_valid; int /*<<< orphan*/  ha; int /*<<< orphan*/  rif; TYPE_1__ key; } ;
struct mlxsw_sp {int /*<<< orphan*/  core; } ;
typedef  enum mlxsw_reg_rauht_op { ____Placeholder_mlxsw_reg_rauht_op } mlxsw_reg_rauht_op ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG (int /*<<< orphan*/ ) ; 
 int MLXSW_REG_RAUHT_LEN ; 
 int /*<<< orphan*/  mlxsw_reg_rauht_pack4 (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_rauht_pack_counter (char*,int /*<<< orphan*/ ) ; 
 int mlxsw_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rauht ; 

__attribute__((used)) static int
mlxsw_sp_router_neigh_entry_op4(struct mlxsw_sp *mlxsw_sp,
				struct mlxsw_sp_neigh_entry *neigh_entry,
				enum mlxsw_reg_rauht_op op)
{
	struct neighbour *n = neigh_entry->key.n;
	u32 dip = ntohl(*((__be32 *) n->primary_key));
	char rauht_pl[MLXSW_REG_RAUHT_LEN];

	mlxsw_reg_rauht_pack4(rauht_pl, op, neigh_entry->rif, neigh_entry->ha,
			      dip);
	if (neigh_entry->counter_valid)
		mlxsw_reg_rauht_pack_counter(rauht_pl,
					     neigh_entry->counter_index);
	return mlxsw_reg_write(mlxsw_sp->core, MLXSW_REG(rauht), rauht_pl);
}