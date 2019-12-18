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
typedef  int /*<<< orphan*/  u32 ;
struct mlx5e_channel {TYPE_1__* stats; int /*<<< orphan*/  netdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  eqn; int /*<<< orphan*/  irqn; int /*<<< orphan*/  cons_index; } ;
struct mlx5_eq_comp {TYPE_2__ core; } ;
struct TYPE_3__ {int /*<<< orphan*/  eq_rearm; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  mlx5_eq_poll_irq_disabled (struct mlx5_eq_comp*) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 

int mlx5e_health_channel_eq_recover(struct mlx5_eq_comp *eq, struct mlx5e_channel *channel)
{
	u32 eqe_count;

	netdev_err(channel->netdev, "EQ 0x%x: Cons = 0x%x, irqn = 0x%x\n",
		   eq->core.eqn, eq->core.cons_index, eq->core.irqn);

	eqe_count = mlx5_eq_poll_irq_disabled(eq);
	if (!eqe_count)
		return -EIO;

	netdev_err(channel->netdev, "Recovered %d eqes on EQ 0x%x\n",
		   eqe_count, eq->core.eqn);

	channel->stats->eq_rearm++;
	return 0;
}