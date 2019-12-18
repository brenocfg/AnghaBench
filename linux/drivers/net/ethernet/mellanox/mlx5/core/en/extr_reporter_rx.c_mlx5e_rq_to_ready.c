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
struct net_device {int dummy; } ;
struct mlx5e_rq {int /*<<< orphan*/  rqn; struct net_device* netdev; } ;

/* Variables and functions */
 int MLX5_RQC_STATE_RDY ; 
 int MLX5_RQC_STATE_RST ; 
 int mlx5e_modify_rq_state (struct mlx5e_rq*,int,int) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mlx5e_rq_to_ready(struct mlx5e_rq *rq, int curr_state)
{
	struct net_device *dev = rq->netdev;
	int err;

	err = mlx5e_modify_rq_state(rq, curr_state, MLX5_RQC_STATE_RST);
	if (err) {
		netdev_err(dev, "Failed to move rq 0x%x to reset\n", rq->rqn);
		return err;
	}
	err = mlx5e_modify_rq_state(rq, MLX5_RQC_STATE_RST, MLX5_RQC_STATE_RDY);
	if (err) {
		netdev_err(dev, "Failed to move rq 0x%x to ready\n", rq->rqn);
		return err;
	}

	return 0;
}