#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int dummy; } ;
struct TYPE_7__ {struct mlx5_eq* eq; } ;
struct TYPE_8__ {TYPE_3__ mcq; } ;
struct mlx5e_txqsq {TYPE_2__* channel; TYPE_4__ cq; } ;
struct mlx5_eq {int /*<<< orphan*/  eqn; int /*<<< orphan*/  irqn; int /*<<< orphan*/  cons_index; } ;
struct TYPE_6__ {TYPE_1__* stats; } ;
struct TYPE_5__ {int /*<<< orphan*/  eq_rearm; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx5_eq_poll_irq_disabled (struct mlx5_eq*) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static bool mlx5e_tx_timeout_eq_recover(struct net_device *dev,
					struct mlx5e_txqsq *sq)
{
	struct mlx5_eq *eq = sq->cq.mcq.eq;
	u32 eqe_count;

	netdev_err(dev, "EQ 0x%x: Cons = 0x%x, irqn = 0x%x\n",
		   eq->eqn, eq->cons_index, eq->irqn);

	eqe_count = mlx5_eq_poll_irq_disabled(eq);
	if (!eqe_count)
		return false;

	netdev_err(dev, "Recover %d eqes on EQ 0x%x\n", eqe_count, eq->eqn);
	sq->channel->stats->eq_rearm++;
	return true;
}