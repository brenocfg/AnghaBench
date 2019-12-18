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
struct mlx5e_rq {TYPE_1__* channel; int /*<<< orphan*/  state; } ;
struct TYPE_2__ {int /*<<< orphan*/  icosq; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5E_RQ_STATE_ENABLED ; 
 int /*<<< orphan*/  mlx5e_trigger_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void mlx5e_activate_rq(struct mlx5e_rq *rq)
{
	set_bit(MLX5E_RQ_STATE_ENABLED, &rq->state);
	mlx5e_trigger_irq(&rq->channel->icosq);
}