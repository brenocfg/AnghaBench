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
struct mlx5e_icosq {int /*<<< orphan*/  sqn; struct mlx5e_channel* channel; } ;
struct mlx5e_channel {int /*<<< orphan*/  mdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx5e_destroy_sq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5e_free_icosq (struct mlx5e_icosq*) ; 

void mlx5e_close_icosq(struct mlx5e_icosq *sq)
{
	struct mlx5e_channel *c = sq->channel;

	mlx5e_destroy_sq(c->mdev, sq->sqn);
	mlx5e_free_icosq(sq);
}