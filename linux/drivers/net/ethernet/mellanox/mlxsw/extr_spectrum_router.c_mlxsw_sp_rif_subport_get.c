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
struct netlink_ext_ack {int dummy; } ;
struct mlxsw_sp_rif_subport {int /*<<< orphan*/  ref_count; } ;
struct mlxsw_sp_rif_params {int /*<<< orphan*/  dev; } ;
struct mlxsw_sp_rif {int dummy; } ;
struct mlxsw_sp {int dummy; } ;

/* Variables and functions */
 struct mlxsw_sp_rif* mlxsw_sp_rif_create (struct mlxsw_sp*,struct mlxsw_sp_rif_params const*,struct netlink_ext_ack*) ; 
 struct mlxsw_sp_rif* mlxsw_sp_rif_find_by_dev (struct mlxsw_sp*,int /*<<< orphan*/ ) ; 
 struct mlxsw_sp_rif_subport* mlxsw_sp_rif_subport_rif (struct mlxsw_sp_rif*) ; 
 int /*<<< orphan*/  refcount_inc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct mlxsw_sp_rif *
mlxsw_sp_rif_subport_get(struct mlxsw_sp *mlxsw_sp,
			 const struct mlxsw_sp_rif_params *params,
			 struct netlink_ext_ack *extack)
{
	struct mlxsw_sp_rif_subport *rif_subport;
	struct mlxsw_sp_rif *rif;

	rif = mlxsw_sp_rif_find_by_dev(mlxsw_sp, params->dev);
	if (!rif)
		return mlxsw_sp_rif_create(mlxsw_sp, params, extack);

	rif_subport = mlxsw_sp_rif_subport_rif(rif);
	refcount_inc(&rif_subport->ref_count);
	return rif;
}