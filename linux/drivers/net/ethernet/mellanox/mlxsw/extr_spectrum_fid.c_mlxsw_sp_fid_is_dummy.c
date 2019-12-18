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
typedef  scalar_t__ u16 ;
struct mlxsw_sp_fid_family {scalar_t__ start_index; } ;
struct mlxsw_sp {TYPE_1__* fid_core; } ;
typedef  enum mlxsw_sp_fid_type { ____Placeholder_mlxsw_sp_fid_type } mlxsw_sp_fid_type ;
struct TYPE_2__ {struct mlxsw_sp_fid_family** fid_family_arr; } ;

/* Variables and functions */
 int MLXSW_SP_FID_TYPE_DUMMY ; 

bool mlxsw_sp_fid_is_dummy(struct mlxsw_sp *mlxsw_sp, u16 fid_index)
{
	enum mlxsw_sp_fid_type fid_type = MLXSW_SP_FID_TYPE_DUMMY;
	struct mlxsw_sp_fid_family *fid_family;

	fid_family = mlxsw_sp->fid_core->fid_family_arr[fid_type];

	return fid_family->start_index == fid_index;
}