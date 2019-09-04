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
struct dma_chan {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct cppi41_dd {TYPE_1__ ddev; int /*<<< orphan*/  lock; int /*<<< orphan*/  is_suspended; int /*<<< orphan*/  pending; } ;
struct cppi41_channel {int /*<<< orphan*/  node; struct cppi41_dd* cdd; } ;

/* Variables and functions */
 int EINPROGRESS ; 
 int /*<<< orphan*/  cppi41_run_queue (struct cppi41_dd*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int pm_runtime_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct cppi41_channel* to_cpp41_chan (struct dma_chan*) ; 

__attribute__((used)) static void cppi41_dma_issue_pending(struct dma_chan *chan)
{
	struct cppi41_channel *c = to_cpp41_chan(chan);
	struct cppi41_dd *cdd = c->cdd;
	unsigned long flags;
	int error;

	error = pm_runtime_get(cdd->ddev.dev);
	if ((error != -EINPROGRESS) && error < 0) {
		pm_runtime_put_noidle(cdd->ddev.dev);
		dev_err(cdd->ddev.dev, "Failed to pm_runtime_get: %i\n",
			error);

		return;
	}

	spin_lock_irqsave(&cdd->lock, flags);
	list_add_tail(&c->node, &cdd->pending);
	if (!cdd->is_suspended)
		cppi41_run_queue(cdd);
	spin_unlock_irqrestore(&cdd->lock, flags);

	pm_runtime_mark_last_busy(cdd->ddev.dev);
	pm_runtime_put_autosuspend(cdd->ddev.dev);
}