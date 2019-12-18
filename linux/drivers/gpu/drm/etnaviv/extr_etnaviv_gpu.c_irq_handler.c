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
typedef  int u32 ;
struct etnaviv_gpu {int sync_point_event; int /*<<< orphan*/  completed_fence; TYPE_1__* event; int /*<<< orphan*/  sync_point_work; int /*<<< orphan*/  wq; int /*<<< orphan*/  dev; } ;
struct dma_fence {int /*<<< orphan*/  seqno; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {struct dma_fence* fence; scalar_t__ sync_point; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  VIVS_HI_INTR_ACKNOWLEDGE ; 
 int VIVS_HI_INTR_ACKNOWLEDGE_AXI_BUS_ERROR ; 
 int VIVS_HI_INTR_ACKNOWLEDGE_MMU_EXCEPTION ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dma_fence_signal (struct dma_fence*) ; 
 int /*<<< orphan*/  dump_mmu_fault (struct etnaviv_gpu*) ; 
 int /*<<< orphan*/  event_free (struct etnaviv_gpu*,int) ; 
 scalar_t__ fence_after (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ffs (int) ; 
 int gpu_read (struct etnaviv_gpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t irq_handler(int irq, void *data)
{
	struct etnaviv_gpu *gpu = data;
	irqreturn_t ret = IRQ_NONE;

	u32 intr = gpu_read(gpu, VIVS_HI_INTR_ACKNOWLEDGE);

	if (intr != 0) {
		int event;

		pm_runtime_mark_last_busy(gpu->dev);

		dev_dbg(gpu->dev, "intr 0x%08x\n", intr);

		if (intr & VIVS_HI_INTR_ACKNOWLEDGE_AXI_BUS_ERROR) {
			dev_err(gpu->dev, "AXI bus error\n");
			intr &= ~VIVS_HI_INTR_ACKNOWLEDGE_AXI_BUS_ERROR;
		}

		if (intr & VIVS_HI_INTR_ACKNOWLEDGE_MMU_EXCEPTION) {
			dump_mmu_fault(gpu);
			intr &= ~VIVS_HI_INTR_ACKNOWLEDGE_MMU_EXCEPTION;
		}

		while ((event = ffs(intr)) != 0) {
			struct dma_fence *fence;

			event -= 1;

			intr &= ~(1 << event);

			dev_dbg(gpu->dev, "event %u\n", event);

			if (gpu->event[event].sync_point) {
				gpu->sync_point_event = event;
				queue_work(gpu->wq, &gpu->sync_point_work);
			}

			fence = gpu->event[event].fence;
			if (!fence)
				continue;

			gpu->event[event].fence = NULL;

			/*
			 * Events can be processed out of order.  Eg,
			 * - allocate and queue event 0
			 * - allocate event 1
			 * - event 0 completes, we process it
			 * - allocate and queue event 0
			 * - event 1 and event 0 complete
			 * we can end up processing event 0 first, then 1.
			 */
			if (fence_after(fence->seqno, gpu->completed_fence))
				gpu->completed_fence = fence->seqno;
			dma_fence_signal(fence);

			event_free(gpu, event);
		}

		ret = IRQ_HANDLED;
	}

	return ret;
}