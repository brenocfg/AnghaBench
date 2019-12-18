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
struct msm_ringbuffer {size_t id; int /*<<< orphan*/  lock; } ;
struct msm_gpu {int nr_rings; } ;
struct adreno_gpu {int dummy; } ;
struct a5xx_gpu {int /*<<< orphan*/  preempt_timer; struct msm_ringbuffer* next_ring; int /*<<< orphan*/ * preempt_iova; TYPE_1__** preempt; struct msm_ringbuffer* cur_ring; } ;
struct TYPE_2__ {int /*<<< orphan*/  wptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  PREEMPT_ABORT ; 
 int /*<<< orphan*/  PREEMPT_NONE ; 
 int /*<<< orphan*/  PREEMPT_START ; 
 int /*<<< orphan*/  PREEMPT_TRIGGERED ; 
 int /*<<< orphan*/  REG_A5XX_CP_CONTEXT_SWITCH_CNTL ; 
 int /*<<< orphan*/  REG_A5XX_CP_CONTEXT_SWITCH_RESTORE_ADDR_HI ; 
 int /*<<< orphan*/  REG_A5XX_CP_CONTEXT_SWITCH_RESTORE_ADDR_LO ; 
 struct msm_ringbuffer* get_next_ring (struct msm_gpu*) ; 
 int /*<<< orphan*/  get_wptr (struct msm_ringbuffer*) ; 
 int /*<<< orphan*/  gpu_write (struct msm_gpu*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gpu_write64 (struct msm_gpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  set_preempt_state (struct a5xx_gpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct a5xx_gpu* to_a5xx_gpu (struct adreno_gpu*) ; 
 struct adreno_gpu* to_adreno_gpu (struct msm_gpu*) ; 
 int /*<<< orphan*/  try_preempt_state (struct a5xx_gpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_wptr (struct msm_gpu*,struct msm_ringbuffer*) ; 
 int /*<<< orphan*/  wmb () ; 

void a5xx_preempt_trigger(struct msm_gpu *gpu)
{
	struct adreno_gpu *adreno_gpu = to_adreno_gpu(gpu);
	struct a5xx_gpu *a5xx_gpu = to_a5xx_gpu(adreno_gpu);
	unsigned long flags;
	struct msm_ringbuffer *ring;

	if (gpu->nr_rings == 1)
		return;

	/*
	 * Try to start preemption by moving from NONE to START. If
	 * unsuccessful, a preemption is already in flight
	 */
	if (!try_preempt_state(a5xx_gpu, PREEMPT_NONE, PREEMPT_START))
		return;

	/* Get the next ring to preempt to */
	ring = get_next_ring(gpu);

	/*
	 * If no ring is populated or the highest priority ring is the current
	 * one do nothing except to update the wptr to the latest and greatest
	 */
	if (!ring || (a5xx_gpu->cur_ring == ring)) {
		/*
		 * Its possible that while a preemption request is in progress
		 * from an irq context, a user context trying to submit might
		 * fail to update the write pointer, because it determines
		 * that the preempt state is not PREEMPT_NONE.
		 *
		 * Close the race by introducing an intermediate
		 * state PREEMPT_ABORT to let the submit path
		 * know that the ringbuffer is not going to change
		 * and can safely update the write pointer.
		 */

		set_preempt_state(a5xx_gpu, PREEMPT_ABORT);
		update_wptr(gpu, a5xx_gpu->cur_ring);
		set_preempt_state(a5xx_gpu, PREEMPT_NONE);
		return;
	}

	/* Make sure the wptr doesn't update while we're in motion */
	spin_lock_irqsave(&ring->lock, flags);
	a5xx_gpu->preempt[ring->id]->wptr = get_wptr(ring);
	spin_unlock_irqrestore(&ring->lock, flags);

	/* Set the address of the incoming preemption record */
	gpu_write64(gpu, REG_A5XX_CP_CONTEXT_SWITCH_RESTORE_ADDR_LO,
		REG_A5XX_CP_CONTEXT_SWITCH_RESTORE_ADDR_HI,
		a5xx_gpu->preempt_iova[ring->id]);

	a5xx_gpu->next_ring = ring;

	/* Start a timer to catch a stuck preemption */
	mod_timer(&a5xx_gpu->preempt_timer, jiffies + msecs_to_jiffies(10000));

	/* Set the preemption state to triggered */
	set_preempt_state(a5xx_gpu, PREEMPT_TRIGGERED);

	/* Make sure everything is written before hitting the button */
	wmb();

	/* And actually start the preemption */
	gpu_write(gpu, REG_A5XX_CP_CONTEXT_SWITCH_CNTL, 1);
}