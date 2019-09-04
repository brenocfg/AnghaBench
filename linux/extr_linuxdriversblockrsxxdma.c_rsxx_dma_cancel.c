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
struct TYPE_2__ {int /*<<< orphan*/  hw_q_depth; } ;
struct rsxx_dma_ctrl {int /*<<< orphan*/  trackers; TYPE_1__ stats; } ;
struct rsxx_dma {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_CANCELLED ; 
 int RSXX_MAX_OUTSTANDING_CMDS ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 struct rsxx_dma* get_tracker_dma (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  push_tracker (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rsxx_complete_dma (struct rsxx_dma_ctrl*,struct rsxx_dma*,int /*<<< orphan*/ ) ; 

int rsxx_dma_cancel(struct rsxx_dma_ctrl *ctrl)
{
	struct rsxx_dma *dma;
	int i;
	int cnt = 0;

	/* Clean up issued DMAs */
	for (i = 0; i < RSXX_MAX_OUTSTANDING_CMDS; i++) {
		dma = get_tracker_dma(ctrl->trackers, i);
		if (dma) {
			atomic_dec(&ctrl->stats.hw_q_depth);
			rsxx_complete_dma(ctrl, dma, DMA_CANCELLED);
			push_tracker(ctrl->trackers, i);
			cnt++;
		}
	}

	return cnt;
}