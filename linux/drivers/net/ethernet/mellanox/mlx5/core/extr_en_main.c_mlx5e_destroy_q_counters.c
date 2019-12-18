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
struct mlx5e_priv {scalar_t__ drop_rq_q_counter; int /*<<< orphan*/  mdev; scalar_t__ q_counter; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx5_core_dealloc_q_counter (int /*<<< orphan*/ ,scalar_t__) ; 

void mlx5e_destroy_q_counters(struct mlx5e_priv *priv)
{
	if (priv->q_counter)
		mlx5_core_dealloc_q_counter(priv->mdev, priv->q_counter);

	if (priv->drop_rq_q_counter)
		mlx5_core_dealloc_q_counter(priv->mdev, priv->drop_rq_q_counter);
}