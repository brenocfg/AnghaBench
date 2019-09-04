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
struct dma_pl330_desc {int /*<<< orphan*/  status; struct dma_pl330_chan* pchan; } ;
struct dma_pl330_chan {int /*<<< orphan*/  task; int /*<<< orphan*/  lock; } ;
typedef  enum pl330_op_err { ____Placeholder_pl330_op_err } pl330_op_err ;

/* Variables and functions */
 int /*<<< orphan*/  DONE ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dma_pl330_rqcb(struct dma_pl330_desc *desc, enum pl330_op_err err)
{
	struct dma_pl330_chan *pch;
	unsigned long flags;

	if (!desc)
		return;

	pch = desc->pchan;

	/* If desc aborted */
	if (!pch)
		return;

	spin_lock_irqsave(&pch->lock, flags);

	desc->status = DONE;

	spin_unlock_irqrestore(&pch->lock, flags);

	tasklet_schedule(&pch->task);
}