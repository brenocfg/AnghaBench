#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int send_flags; int /*<<< orphan*/  opcode; } ;
struct mlx5_umr_wr {int ignore_free_state; int /*<<< orphan*/  mkey; int /*<<< orphan*/  pd; TYPE_3__ wr; } ;
struct TYPE_5__ {int /*<<< orphan*/  key; } ;
struct mlx5_ib_mr {TYPE_2__ mmkey; } ;
struct TYPE_4__ {int /*<<< orphan*/  pd; } ;
struct mlx5_ib_dev {TYPE_1__ umrc; struct mlx5_core_dev* mdev; } ;
struct mlx5_core_dev {scalar_t__ state; } ;

/* Variables and functions */
 scalar_t__ MLX5_DEVICE_STATE_INTERNAL_ERROR ; 
 int MLX5_IB_SEND_UMR_DISABLE_MR ; 
 int MLX5_IB_SEND_UMR_UPDATE_PD_ACCESS ; 
 int /*<<< orphan*/  MLX5_IB_WR_UMR ; 
 int mlx5_ib_post_send_wait (struct mlx5_ib_dev*,struct mlx5_umr_wr*) ; 

__attribute__((used)) static int unreg_umr(struct mlx5_ib_dev *dev, struct mlx5_ib_mr *mr)
{
	struct mlx5_core_dev *mdev = dev->mdev;
	struct mlx5_umr_wr umrwr = {};

	if (mdev->state == MLX5_DEVICE_STATE_INTERNAL_ERROR)
		return 0;

	umrwr.wr.send_flags = MLX5_IB_SEND_UMR_DISABLE_MR |
			      MLX5_IB_SEND_UMR_UPDATE_PD_ACCESS;
	umrwr.wr.opcode = MLX5_IB_WR_UMR;
	umrwr.pd = dev->umrc.pd;
	umrwr.mkey = mr->mmkey.key;
	umrwr.ignore_free_state = 1;

	return mlx5_ib_post_send_wait(dev, &umrwr);
}