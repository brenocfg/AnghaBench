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
struct mlxsw_sp_nve_mc_record {int dummy; } ;
struct mlxsw_sp_nve_mc_list {int dummy; } ;
struct mlxsw_sp {int dummy; } ;
typedef  enum mlxsw_sp_l3proto { ____Placeholder_mlxsw_sp_l3proto } mlxsw_sp_l3proto ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct mlxsw_sp_nve_mc_record*) ; 
 int PTR_ERR (struct mlxsw_sp_nve_mc_record*) ; 
 struct mlxsw_sp_nve_mc_record* mlxsw_sp_nve_mc_record_get (struct mlxsw_sp*,struct mlxsw_sp_nve_mc_list*,int) ; 
 int mlxsw_sp_nve_mc_record_ip_add (struct mlxsw_sp_nve_mc_record*,union mlxsw_sp_l3addr*) ; 
 int /*<<< orphan*/  mlxsw_sp_nve_mc_record_put (struct mlxsw_sp_nve_mc_record*) ; 

__attribute__((used)) static int mlxsw_sp_nve_mc_list_ip_add(struct mlxsw_sp *mlxsw_sp,
				       struct mlxsw_sp_nve_mc_list *mc_list,
				       enum mlxsw_sp_l3proto proto,
				       union mlxsw_sp_l3addr *addr)
{
	struct mlxsw_sp_nve_mc_record *mc_record;
	int err;

	mc_record = mlxsw_sp_nve_mc_record_get(mlxsw_sp, mc_list, proto);
	if (IS_ERR(mc_record))
		return PTR_ERR(mc_record);

	err = mlxsw_sp_nve_mc_record_ip_add(mc_record, addr);
	if (err)
		goto err_ip_add;

	return 0;

err_ip_add:
	mlxsw_sp_nve_mc_record_put(mc_record);
	return err;
}