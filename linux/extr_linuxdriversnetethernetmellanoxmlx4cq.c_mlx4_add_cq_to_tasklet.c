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
struct mlx4_eq_tasklet {int /*<<< orphan*/  lock; int /*<<< orphan*/  task; int /*<<< orphan*/  list; } ;
struct TYPE_2__ {int /*<<< orphan*/  list; struct mlx4_eq_tasklet* priv; } ;
struct mlx4_cq {TYPE_1__ tasklet_ctx; int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int list_empty (int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty_careful (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mlx4_add_cq_to_tasklet(struct mlx4_cq *cq)
{
	struct mlx4_eq_tasklet *tasklet_ctx = cq->tasklet_ctx.priv;
	unsigned long flags;
	bool kick;

	spin_lock_irqsave(&tasklet_ctx->lock, flags);
	/* When migrating CQs between EQs will be implemented, please note
	 * that you need to sync this point. It is possible that
	 * while migrating a CQ, completions on the old EQs could
	 * still arrive.
	 */
	if (list_empty_careful(&cq->tasklet_ctx.list)) {
		refcount_inc(&cq->refcount);
		kick = list_empty(&tasklet_ctx->list);
		list_add_tail(&cq->tasklet_ctx.list, &tasklet_ctx->list);
		if (kick)
			tasklet_schedule(&tasklet_ctx->task);
	}
	spin_unlock_irqrestore(&tasklet_ctx->lock, flags);
}