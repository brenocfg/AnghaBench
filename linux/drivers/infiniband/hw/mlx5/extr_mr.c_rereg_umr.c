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
struct TYPE_4__ {int /*<<< orphan*/  send_flags; int /*<<< orphan*/  opcode; } ;
struct mlx5_umr_wr {int access_flags; TYPE_2__ wr; struct ib_pd* pd; int /*<<< orphan*/  mkey; } ;
struct TYPE_3__ {int /*<<< orphan*/  key; } ;
struct mlx5_ib_mr {TYPE_1__ mmkey; } ;
struct mlx5_ib_dev {int dummy; } ;
struct ib_pd {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int IB_MR_REREG_ACCESS ; 
 int IB_MR_REREG_PD ; 
 int /*<<< orphan*/  MLX5_IB_SEND_UMR_FAIL_IF_FREE ; 
 int /*<<< orphan*/  MLX5_IB_SEND_UMR_UPDATE_PD_ACCESS ; 
 int /*<<< orphan*/  MLX5_IB_WR_UMR ; 
 int mlx5_ib_post_send_wait (struct mlx5_ib_dev*,struct mlx5_umr_wr*) ; 
 struct mlx5_ib_dev* to_mdev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rereg_umr(struct ib_pd *pd, struct mlx5_ib_mr *mr,
		     int access_flags, int flags)
{
	struct mlx5_ib_dev *dev = to_mdev(pd->device);
	struct mlx5_umr_wr umrwr = {};
	int err;

	umrwr.wr.send_flags = MLX5_IB_SEND_UMR_FAIL_IF_FREE;

	umrwr.wr.opcode = MLX5_IB_WR_UMR;
	umrwr.mkey = mr->mmkey.key;

	if (flags & IB_MR_REREG_PD || flags & IB_MR_REREG_ACCESS) {
		umrwr.pd = pd;
		umrwr.access_flags = access_flags;
		umrwr.wr.send_flags |= MLX5_IB_SEND_UMR_UPDATE_PD_ACCESS;
	}

	err = mlx5_ib_post_send_wait(dev, &umrwr);

	return err;
}