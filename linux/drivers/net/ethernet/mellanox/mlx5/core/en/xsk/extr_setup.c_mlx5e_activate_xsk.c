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
struct TYPE_2__ {int /*<<< orphan*/  state; } ;
struct mlx5e_channel {int /*<<< orphan*/  xskicosq_lock; int /*<<< orphan*/  xskicosq; TYPE_1__ xskrq; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5E_RQ_STATE_ENABLED ; 
 int /*<<< orphan*/  mlx5e_activate_icosq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5e_trigger_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void mlx5e_activate_xsk(struct mlx5e_channel *c)
{
	mlx5e_activate_icosq(&c->xskicosq);
	set_bit(MLX5E_RQ_STATE_ENABLED, &c->xskrq.state);
	/* TX queue is created active. */

	spin_lock(&c->xskicosq_lock);
	mlx5e_trigger_irq(&c->xskicosq);
	spin_unlock(&c->xskicosq_lock);
}