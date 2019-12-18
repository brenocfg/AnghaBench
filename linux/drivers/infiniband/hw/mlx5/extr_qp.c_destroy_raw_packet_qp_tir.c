#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct mlx5_ib_rq {int /*<<< orphan*/  tirn; } ;
struct mlx5_ib_dev {int /*<<< orphan*/  mdev; } ;
struct ib_pd {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  uid; } ;

/* Variables and functions */
 int MLX5_QP_FLAG_TIR_ALLOW_SELF_LB_MC ; 
 int MLX5_QP_FLAG_TIR_ALLOW_SELF_LB_UC ; 
 int /*<<< orphan*/  mlx5_cmd_destroy_tir (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_ib_disable_lb (struct mlx5_ib_dev*,int,int) ; 
 TYPE_1__* to_mpd (struct ib_pd*) ; 

__attribute__((used)) static void destroy_raw_packet_qp_tir(struct mlx5_ib_dev *dev,
				      struct mlx5_ib_rq *rq,
				      u32 qp_flags_en,
				      struct ib_pd *pd)
{
	if (qp_flags_en & (MLX5_QP_FLAG_TIR_ALLOW_SELF_LB_UC |
			   MLX5_QP_FLAG_TIR_ALLOW_SELF_LB_MC))
		mlx5_ib_disable_lb(dev, false, true);
	mlx5_cmd_destroy_tir(dev->mdev, rq->tirn, to_mpd(pd)->uid);
}