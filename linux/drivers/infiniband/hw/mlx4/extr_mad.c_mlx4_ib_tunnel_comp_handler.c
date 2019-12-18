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
struct TYPE_2__ {int /*<<< orphan*/  going_down_lock; int /*<<< orphan*/  is_going_down; } ;
struct mlx4_ib_dev {TYPE_1__ sriov; } ;
struct mlx4_ib_demux_pv_ctx {scalar_t__ state; int /*<<< orphan*/  work; int /*<<< orphan*/  wq; int /*<<< orphan*/  ib_dev; } ;
struct ib_cq {struct mlx4_ib_demux_pv_ctx* cq_context; } ;

/* Variables and functions */
 scalar_t__ DEMUX_PV_STATE_ACTIVE ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct mlx4_ib_dev* to_mdev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mlx4_ib_tunnel_comp_handler(struct ib_cq *cq, void *arg)
{
	unsigned long flags;
	struct mlx4_ib_demux_pv_ctx *ctx = cq->cq_context;
	struct mlx4_ib_dev *dev = to_mdev(ctx->ib_dev);
	spin_lock_irqsave(&dev->sriov.going_down_lock, flags);
	if (!dev->sriov.is_going_down && ctx->state == DEMUX_PV_STATE_ACTIVE)
		queue_work(ctx->wq, &ctx->work);
	spin_unlock_irqrestore(&dev->sriov.going_down_lock, flags);
}