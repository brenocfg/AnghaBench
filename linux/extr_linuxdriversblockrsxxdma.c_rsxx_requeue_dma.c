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
struct TYPE_2__ {int /*<<< orphan*/  sw_q_depth; } ;
struct rsxx_dma_ctrl {int /*<<< orphan*/  queue_lock; int /*<<< orphan*/  queue; TYPE_1__ stats; } ;
struct rsxx_dma {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rsxx_requeue_dma(struct rsxx_dma_ctrl *ctrl,
				 struct rsxx_dma *dma)
{
	/*
	 * Requeued DMAs go to the front of the queue so they are issued
	 * first.
	 */
	spin_lock_bh(&ctrl->queue_lock);
	ctrl->stats.sw_q_depth++;
	list_add(&dma->list, &ctrl->queue);
	spin_unlock_bh(&ctrl->queue_lock);
}