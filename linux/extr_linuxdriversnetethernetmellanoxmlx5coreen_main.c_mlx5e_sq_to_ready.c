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
struct net_device {int dummy; } ;
struct mlx5e_txqsq {int /*<<< orphan*/  sqn; TYPE_1__* channel; } ;
struct mlx5e_modify_sq_param {int curr_state; void* next_state; int /*<<< orphan*/  member_0; } ;
struct mlx5_core_dev {int dummy; } ;
typedef  int /*<<< orphan*/  msp ;
struct TYPE_2__ {struct net_device* netdev; struct mlx5_core_dev* mdev; } ;

/* Variables and functions */
 void* MLX5_SQC_STATE_RDY ; 
 void* MLX5_SQC_STATE_RST ; 
 int /*<<< orphan*/  memset (struct mlx5e_modify_sq_param*,int /*<<< orphan*/ ,int) ; 
 int mlx5e_modify_sq (struct mlx5_core_dev*,int /*<<< orphan*/ ,struct mlx5e_modify_sq_param*) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mlx5e_sq_to_ready(struct mlx5e_txqsq *sq, int curr_state)
{
	struct mlx5_core_dev *mdev = sq->channel->mdev;
	struct net_device *dev = sq->channel->netdev;
	struct mlx5e_modify_sq_param msp = {0};
	int err;

	msp.curr_state = curr_state;
	msp.next_state = MLX5_SQC_STATE_RST;

	err = mlx5e_modify_sq(mdev, sq->sqn, &msp);
	if (err) {
		netdev_err(dev, "Failed to move sq 0x%x to reset\n", sq->sqn);
		return err;
	}

	memset(&msp, 0, sizeof(msp));
	msp.curr_state = MLX5_SQC_STATE_RST;
	msp.next_state = MLX5_SQC_STATE_RDY;

	err = mlx5e_modify_sq(mdev, sq->sqn, &msp);
	if (err) {
		netdev_err(dev, "Failed to move sq 0x%x to ready\n", sq->sqn);
		return err;
	}

	return 0;
}