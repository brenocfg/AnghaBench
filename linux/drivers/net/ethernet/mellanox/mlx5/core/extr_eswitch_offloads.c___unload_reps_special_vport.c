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
typedef  int /*<<< orphan*/  u8 ;
struct mlx5_eswitch_rep {int dummy; } ;
struct mlx5_eswitch {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5_VPORT_ECPF ; 
 int /*<<< orphan*/  MLX5_VPORT_PF ; 
 int /*<<< orphan*/  MLX5_VPORT_UPLINK ; 
 int /*<<< orphan*/  __esw_offloads_unload_rep (struct mlx5_eswitch*,struct mlx5_eswitch_rep*,int /*<<< orphan*/ ) ; 
 scalar_t__ mlx5_core_is_ecpf_esw_manager (int /*<<< orphan*/ ) ; 
 scalar_t__ mlx5_ecpf_vport_exists (int /*<<< orphan*/ ) ; 
 struct mlx5_eswitch_rep* mlx5_eswitch_get_rep (struct mlx5_eswitch*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __unload_reps_special_vport(struct mlx5_eswitch *esw, u8 rep_type)
{
	struct mlx5_eswitch_rep *rep;

	if (mlx5_ecpf_vport_exists(esw->dev)) {
		rep = mlx5_eswitch_get_rep(esw, MLX5_VPORT_ECPF);
		__esw_offloads_unload_rep(esw, rep, rep_type);
	}

	if (mlx5_core_is_ecpf_esw_manager(esw->dev)) {
		rep = mlx5_eswitch_get_rep(esw, MLX5_VPORT_PF);
		__esw_offloads_unload_rep(esw, rep, rep_type);
	}

	rep = mlx5_eswitch_get_rep(esw, MLX5_VPORT_UPLINK);
	__esw_offloads_unload_rep(esw, rep, rep_type);
}