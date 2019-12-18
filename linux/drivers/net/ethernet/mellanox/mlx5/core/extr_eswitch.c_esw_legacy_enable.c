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
struct mlx5_eswitch {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5_LEGACY_SRIOV_VPORT_EVENTS ; 
 int esw_create_legacy_table (struct mlx5_eswitch*) ; 
 int /*<<< orphan*/  mlx5_eswitch_enable_pf_vf_vports (struct mlx5_eswitch*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int esw_legacy_enable(struct mlx5_eswitch *esw)
{
	int ret;

	ret = esw_create_legacy_table(esw);
	if (ret)
		return ret;

	mlx5_eswitch_enable_pf_vf_vports(esw, MLX5_LEGACY_SRIOV_VPORT_EVENTS);
	return 0;
}