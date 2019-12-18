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
struct mlx5e_priv {int /*<<< orphan*/  update_stats_work; int /*<<< orphan*/  wq; int /*<<< orphan*/  state; TYPE_1__* profile; } ;
struct TYPE_2__ {int /*<<< orphan*/  update_stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5E_STATE_DESTROYING ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

void mlx5e_queue_update_stats(struct mlx5e_priv *priv)
{
	if (!priv->profile->update_stats)
		return;

	if (unlikely(test_bit(MLX5E_STATE_DESTROYING, &priv->state)))
		return;

	queue_work(priv->wq, &priv->update_stats_work);
}