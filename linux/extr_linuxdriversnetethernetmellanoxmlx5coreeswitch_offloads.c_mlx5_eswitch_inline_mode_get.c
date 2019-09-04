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
typedef  scalar_t__ u8 ;
struct mlx5_eswitch {scalar_t__ mode; struct mlx5_core_dev* dev; } ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int MLX5_CAP_ETH (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_CAP_GEN (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
#define  MLX5_CAP_INLINE_MODE_L2 130 
#define  MLX5_CAP_INLINE_MODE_NOT_REQUIRED 129 
#define  MLX5_CAP_INLINE_MODE_VPORT_CONTEXT 128 
 scalar_t__ MLX5_INLINE_MODE_L2 ; 
 scalar_t__ MLX5_INLINE_MODE_NONE ; 
 scalar_t__ SRIOV_NONE ; 
 int /*<<< orphan*/  mlx5_query_nic_vport_min_inline (struct mlx5_core_dev*,int,scalar_t__*) ; 
 int /*<<< orphan*/  vport_group_manager ; 
 int /*<<< orphan*/  wqe_inline_mode ; 

int mlx5_eswitch_inline_mode_get(struct mlx5_eswitch *esw, int nvfs, u8 *mode)
{
	u8 prev_mlx5_mode, mlx5_mode = MLX5_INLINE_MODE_L2;
	struct mlx5_core_dev *dev = esw->dev;
	int vport;

	if (!MLX5_CAP_GEN(dev, vport_group_manager))
		return -EOPNOTSUPP;

	if (esw->mode == SRIOV_NONE)
		return -EOPNOTSUPP;

	switch (MLX5_CAP_ETH(dev, wqe_inline_mode)) {
	case MLX5_CAP_INLINE_MODE_NOT_REQUIRED:
		mlx5_mode = MLX5_INLINE_MODE_NONE;
		goto out;
	case MLX5_CAP_INLINE_MODE_L2:
		mlx5_mode = MLX5_INLINE_MODE_L2;
		goto out;
	case MLX5_CAP_INLINE_MODE_VPORT_CONTEXT:
		goto query_vports;
	}

query_vports:
	for (vport = 1; vport <= nvfs; vport++) {
		mlx5_query_nic_vport_min_inline(dev, vport, &mlx5_mode);
		if (vport > 1 && prev_mlx5_mode != mlx5_mode)
			return -EINVAL;
		prev_mlx5_mode = mlx5_mode;
	}

out:
	*mode = mlx5_mode;
	return 0;
}