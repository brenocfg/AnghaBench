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
struct mlxsw_sp_rif_subport {int /*<<< orphan*/  system_port; int /*<<< orphan*/  lag_id; scalar_t__ lag; int /*<<< orphan*/  vid; int /*<<< orphan*/  ref_count; } ;
struct mlxsw_sp_rif_params {int /*<<< orphan*/  system_port; int /*<<< orphan*/  lag_id; scalar_t__ lag; int /*<<< orphan*/  vid; } ;
struct mlxsw_sp_rif {int dummy; } ;

/* Variables and functions */
 struct mlxsw_sp_rif_subport* mlxsw_sp_rif_subport_rif (struct mlxsw_sp_rif*) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void mlxsw_sp_rif_subport_setup(struct mlxsw_sp_rif *rif,
				       const struct mlxsw_sp_rif_params *params)
{
	struct mlxsw_sp_rif_subport *rif_subport;

	rif_subport = mlxsw_sp_rif_subport_rif(rif);
	refcount_set(&rif_subport->ref_count, 1);
	rif_subport->vid = params->vid;
	rif_subport->lag = params->lag;
	if (params->lag)
		rif_subport->lag_id = params->lag_id;
	else
		rif_subport->system_port = params->system_port;
}