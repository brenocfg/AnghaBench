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
struct mlxsw_sp_fid_ops {int (* nve_flood_index_set ) (struct mlxsw_sp_fid*,int /*<<< orphan*/ ) ;} ;
struct mlxsw_sp_fid_family {struct mlxsw_sp_fid_ops* ops; } ;
struct mlxsw_sp_fid {int nve_flood_index_valid; int /*<<< orphan*/  nve_flood_index; struct mlxsw_sp_fid_family* fid_family; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ WARN_ON (int) ; 
 int stub1 (struct mlxsw_sp_fid*,int /*<<< orphan*/ ) ; 

int mlxsw_sp_fid_nve_flood_index_set(struct mlxsw_sp_fid *fid,
				     u32 nve_flood_index)
{
	struct mlxsw_sp_fid_family *fid_family = fid->fid_family;
	const struct mlxsw_sp_fid_ops *ops = fid_family->ops;
	int err;

	if (WARN_ON(!ops->nve_flood_index_set || fid->nve_flood_index_valid))
		return -EINVAL;

	err = ops->nve_flood_index_set(fid, nve_flood_index);
	if (err)
		return err;

	fid->nve_flood_index = nve_flood_index;
	fid->nve_flood_index_valid = true;

	return 0;
}