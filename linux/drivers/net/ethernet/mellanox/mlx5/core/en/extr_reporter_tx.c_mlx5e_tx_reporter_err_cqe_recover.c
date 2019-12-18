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
typedef  scalar_t__ u8 ;
struct net_device {int dummy; } ;
struct mlx5e_txqsq {int /*<<< orphan*/  state; TYPE_1__* stats; int /*<<< orphan*/  sqn; TYPE_2__* channel; int /*<<< orphan*/  txq; } ;
struct mlx5_core_dev {int dummy; } ;
struct TYPE_4__ {struct net_device* netdev; struct mlx5_core_dev* mdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  recover; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5E_SQ_STATE_RECOVERING ; 
 scalar_t__ MLX5_SQC_STATE_ERR ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int mlx5_core_query_sq_state (struct mlx5_core_dev*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  mlx5e_activate_txqsq (struct mlx5e_txqsq*) ; 
 int mlx5e_health_sq_to_ready (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5e_reset_txqsq_cc_pc (struct mlx5e_txqsq*) ; 
 int /*<<< orphan*/  mlx5e_tx_disable_queue (int /*<<< orphan*/ ) ; 
 int mlx5e_wait_for_sq_flush (struct mlx5e_txqsq*) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mlx5e_tx_reporter_err_cqe_recover(void *ctx)
{
	struct mlx5_core_dev *mdev;
	struct net_device *dev;
	struct mlx5e_txqsq *sq;
	u8 state;
	int err;

	sq = ctx;
	mdev = sq->channel->mdev;
	dev = sq->channel->netdev;

	if (!test_bit(MLX5E_SQ_STATE_RECOVERING, &sq->state))
		return 0;

	err = mlx5_core_query_sq_state(mdev, sq->sqn, &state);
	if (err) {
		netdev_err(dev, "Failed to query SQ 0x%x state. err = %d\n",
			   sq->sqn, err);
		goto out;
	}

	if (state != MLX5_SQC_STATE_ERR)
		goto out;

	mlx5e_tx_disable_queue(sq->txq);

	err = mlx5e_wait_for_sq_flush(sq);
	if (err)
		goto out;

	/* At this point, no new packets will arrive from the stack as TXQ is
	 * marked with QUEUE_STATE_DRV_XOFF. In addition, NAPI cleared all
	 * pending WQEs. SQ can safely reset the SQ.
	 */

	err = mlx5e_health_sq_to_ready(sq->channel, sq->sqn);
	if (err)
		goto out;

	mlx5e_reset_txqsq_cc_pc(sq);
	sq->stats->recover++;
	clear_bit(MLX5E_SQ_STATE_RECOVERING, &sq->state);
	mlx5e_activate_txqsq(sq);

	return 0;
out:
	clear_bit(MLX5E_SQ_STATE_RECOVERING, &sq->state);
	return err;
}