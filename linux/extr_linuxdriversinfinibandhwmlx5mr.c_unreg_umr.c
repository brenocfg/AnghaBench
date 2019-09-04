#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int send_flags; int /*<<< orphan*/  opcode; } ;
struct mlx5_umr_wr {int /*<<< orphan*/  mkey; TYPE_1__ wr; } ;
struct TYPE_4__ {int /*<<< orphan*/  key; } ;
struct mlx5_ib_mr {TYPE_2__ mmkey; } ;
struct mlx5_ib_dev {struct mlx5_core_dev* mdev; } ;
struct mlx5_core_dev {scalar_t__ state; } ;

/* Variables and functions */
 scalar_t__ MLX5_DEVICE_STATE_INTERNAL_ERROR ; 
 int MLX5_IB_SEND_UMR_DISABLE_MR ; 
 int MLX5_IB_SEND_UMR_FAIL_IF_FREE ; 
 int /*<<< orphan*/  MLX5_IB_WR_UMR ; 
 int mlx5_ib_post_send_wait (struct mlx5_ib_dev*,struct mlx5_umr_wr*) ; 

__attribute__((used)) static int unreg_umr(struct mlx5_ib_dev *dev, struct mlx5_ib_mr *mr)
{
	struct mlx5_core_dev *mdev = dev->mdev;
	struct mlx5_umr_wr umrwr = {};

	if (mdev->state == MLX5_DEVICE_STATE_INTERNAL_ERROR)
		return 0;

	umrwr.wr.send_flags = MLX5_IB_SEND_UMR_DISABLE_MR |
			      MLX5_IB_SEND_UMR_FAIL_IF_FREE;
	umrwr.wr.opcode = MLX5_IB_WR_UMR;
	umrwr.mkey = mr->mmkey.key;

	return mlx5_ib_post_send_wait(dev, &umrwr);
}