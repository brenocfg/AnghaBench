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
struct mlxsw_sp_fid_core {TYPE_1__** fid_family_arr; } ;
struct mlxsw_sp {struct mlxsw_sp_fid_core* fid_core; } ;
typedef  enum mlxsw_sp_rif_type { ____Placeholder_mlxsw_sp_rif_type } mlxsw_sp_rif_type ;
typedef  enum mlxsw_sp_fid_type { ____Placeholder_mlxsw_sp_fid_type } mlxsw_sp_fid_type ;
struct TYPE_2__ {int rif_type; } ;

/* Variables and functions */

enum mlxsw_sp_rif_type
mlxsw_sp_fid_type_rif_type(const struct mlxsw_sp *mlxsw_sp,
			   enum mlxsw_sp_fid_type type)
{
	struct mlxsw_sp_fid_core *fid_core = mlxsw_sp->fid_core;

	return fid_core->fid_family_arr[type]->rif_type;
}