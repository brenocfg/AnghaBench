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
typedef  int /*<<< orphan*/  u32 ;
struct mlxsw_sp_rif {int dummy; } ;
struct mlxsw_sp_neigh_entry {int dummy; } ;
struct devlink_dpipe_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __mlxsw_sp_dpipe_table_host_entry_fill (struct devlink_dpipe_entry*,struct mlxsw_sp_rif*,unsigned char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlxsw_sp_neigh4_entry_dip (struct mlxsw_sp_neigh_entry*) ; 
 unsigned char* mlxsw_sp_neigh_entry_ha (struct mlxsw_sp_neigh_entry*) ; 

__attribute__((used)) static void
mlxsw_sp_dpipe_table_host4_entry_fill(struct devlink_dpipe_entry *entry,
				      struct mlxsw_sp_neigh_entry *neigh_entry,
				      struct mlxsw_sp_rif *rif)
{
	unsigned char *ha;
	u32 dip;

	ha = mlxsw_sp_neigh_entry_ha(neigh_entry);
	dip = mlxsw_sp_neigh4_entry_dip(neigh_entry);
	__mlxsw_sp_dpipe_table_host_entry_fill(entry, rif, ha, &dip);
}