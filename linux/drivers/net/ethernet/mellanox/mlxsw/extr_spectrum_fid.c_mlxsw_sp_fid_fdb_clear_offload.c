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
struct net_device {int dummy; } ;
struct mlxsw_sp_fid_ops {int /*<<< orphan*/  (* fdb_clear_offload ) (struct mlxsw_sp_fid const*,struct net_device const*) ;} ;
struct mlxsw_sp_fid_family {struct mlxsw_sp_fid_ops* ops; } ;
struct mlxsw_sp_fid {struct mlxsw_sp_fid_family* fid_family; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct mlxsw_sp_fid const*,struct net_device const*) ; 

void mlxsw_sp_fid_fdb_clear_offload(const struct mlxsw_sp_fid *fid,
				    const struct net_device *nve_dev)
{
	struct mlxsw_sp_fid_family *fid_family = fid->fid_family;
	const struct mlxsw_sp_fid_ops *ops = fid_family->ops;

	if (ops->fdb_clear_offload)
		ops->fdb_clear_offload(fid, nve_dev);
}