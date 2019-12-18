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
struct mlx5_eswitch {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5_CAP_ESW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MLX5_CAP_ESW_FLOWTABLE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MLX5_FDB_TO_VPORT_REG_C_0 ; 
 int /*<<< orphan*/  esw_uplink_ingress_acl ; 
 int /*<<< orphan*/  fdb_to_vport_reg_c_id ; 
 int /*<<< orphan*/  flow_source ; 
 scalar_t__ mlx5_core_is_ecpf_esw_manager (int /*<<< orphan*/ ) ; 
 scalar_t__ mlx5_ecpf_vport_exists (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
esw_check_vport_match_metadata_supported(const struct mlx5_eswitch *esw)
{
	if (!MLX5_CAP_ESW(esw->dev, esw_uplink_ingress_acl))
		return false;

	if (!(MLX5_CAP_ESW_FLOWTABLE(esw->dev, fdb_to_vport_reg_c_id) &
	      MLX5_FDB_TO_VPORT_REG_C_0))
		return false;

	if (!MLX5_CAP_ESW_FLOWTABLE(esw->dev, flow_source))
		return false;

	if (mlx5_core_is_ecpf_esw_manager(esw->dev) ||
	    mlx5_ecpf_vport_exists(esw->dev))
		return false;

	return true;
}