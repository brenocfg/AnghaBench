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
struct mlx5e_xdpsq {int /*<<< orphan*/  sqn; int /*<<< orphan*/  state; struct mlx5e_channel* channel; } ;
struct mlx5e_channel {int /*<<< orphan*/  mdev; int /*<<< orphan*/  napi; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5E_SQ_STATE_ENABLED ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5e_destroy_sq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5e_free_xdpsq (struct mlx5e_xdpsq*) ; 
 int /*<<< orphan*/  mlx5e_free_xdpsq_descs (struct mlx5e_xdpsq*) ; 
 int /*<<< orphan*/  napi_synchronize (int /*<<< orphan*/ *) ; 

void mlx5e_close_xdpsq(struct mlx5e_xdpsq *sq)
{
	struct mlx5e_channel *c = sq->channel;

	clear_bit(MLX5E_SQ_STATE_ENABLED, &sq->state);
	napi_synchronize(&c->napi);

	mlx5e_destroy_sq(c->mdev, sq->sqn);
	mlx5e_free_xdpsq_descs(sq);
	mlx5e_free_xdpsq(sq);
}