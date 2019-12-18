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
typedef  scalar_t__ u8 ;
struct net_device {int dummy; } ;
struct mlx5e_rq {int /*<<< orphan*/  state; TYPE_1__* stats; int /*<<< orphan*/  rqn; struct net_device* netdev; struct mlx5_core_dev* mdev; } ;
struct mlx5_core_dev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  recover; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5E_RQ_STATE_RECOVERING ; 
 scalar_t__ MLX5_RQC_STATE_ERR ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5e_activate_rq (struct mlx5e_rq*) ; 
 int /*<<< orphan*/  mlx5e_deactivate_rq (struct mlx5e_rq*) ; 
 int /*<<< orphan*/  mlx5e_free_rx_descs (struct mlx5e_rq*) ; 
 int mlx5e_query_rq_state (struct mlx5_core_dev*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int mlx5e_rq_to_ready (struct mlx5e_rq*,scalar_t__) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mlx5e_rx_reporter_err_rq_cqe_recover(void *ctx)
{
	struct mlx5_core_dev *mdev;
	struct net_device *dev;
	struct mlx5e_rq *rq;
	u8 state;
	int err;

	rq = ctx;
	mdev = rq->mdev;
	dev = rq->netdev;
	err = mlx5e_query_rq_state(mdev, rq->rqn, &state);
	if (err) {
		netdev_err(dev, "Failed to query RQ 0x%x state. err = %d\n",
			   rq->rqn, err);
		goto out;
	}

	if (state != MLX5_RQC_STATE_ERR)
		goto out;

	mlx5e_deactivate_rq(rq);
	mlx5e_free_rx_descs(rq);

	err = mlx5e_rq_to_ready(rq, MLX5_RQC_STATE_ERR);
	if (err)
		goto out;

	clear_bit(MLX5E_RQ_STATE_RECOVERING, &rq->state);
	mlx5e_activate_rq(rq);
	rq->stats->recover++;
	return 0;
out:
	clear_bit(MLX5E_RQ_STATE_RECOVERING, &rq->state);
	return err;
}