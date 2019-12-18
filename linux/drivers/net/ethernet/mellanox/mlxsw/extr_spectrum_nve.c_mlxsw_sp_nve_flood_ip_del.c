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
typedef  union mlxsw_sp_l3addr {int dummy; } mlxsw_sp_l3addr ;
struct mlxsw_sp_nve_mc_list_key {int /*<<< orphan*/  fid_index; int /*<<< orphan*/  member_0; } ;
struct mlxsw_sp_nve_mc_list {int dummy; } ;
struct mlxsw_sp_fid {int dummy; } ;
struct mlxsw_sp {int dummy; } ;
typedef  enum mlxsw_sp_l3proto { ____Placeholder_mlxsw_sp_l3proto } mlxsw_sp_l3proto ;

/* Variables and functions */
 int /*<<< orphan*/  mlxsw_sp_fid_index (struct mlxsw_sp_fid*) ; 
 int /*<<< orphan*/  mlxsw_sp_nve_fid_flood_index_clear (struct mlxsw_sp_fid*,struct mlxsw_sp_nve_mc_list*) ; 
 struct mlxsw_sp_nve_mc_list* mlxsw_sp_nve_mc_list_find (struct mlxsw_sp*,struct mlxsw_sp_nve_mc_list_key*) ; 
 int /*<<< orphan*/  mlxsw_sp_nve_mc_list_ip_del (struct mlxsw_sp*,struct mlxsw_sp_nve_mc_list*,int,union mlxsw_sp_l3addr*) ; 
 int /*<<< orphan*/  mlxsw_sp_nve_mc_list_put (struct mlxsw_sp*,struct mlxsw_sp_nve_mc_list*) ; 

void mlxsw_sp_nve_flood_ip_del(struct mlxsw_sp *mlxsw_sp,
			       struct mlxsw_sp_fid *fid,
			       enum mlxsw_sp_l3proto proto,
			       union mlxsw_sp_l3addr *addr)
{
	struct mlxsw_sp_nve_mc_list_key key = { 0 };
	struct mlxsw_sp_nve_mc_list *mc_list;

	key.fid_index = mlxsw_sp_fid_index(fid);
	mc_list = mlxsw_sp_nve_mc_list_find(mlxsw_sp, &key);
	if (!mc_list)
		return;

	mlxsw_sp_nve_fid_flood_index_clear(fid, mc_list);
	mlxsw_sp_nve_mc_list_ip_del(mlxsw_sp, mc_list, proto, addr);
	mlxsw_sp_nve_mc_list_put(mlxsw_sp, mc_list);
}