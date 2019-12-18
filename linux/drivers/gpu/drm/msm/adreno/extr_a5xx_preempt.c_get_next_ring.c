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
struct msm_ringbuffer {int /*<<< orphan*/  lock; TYPE_1__* memptrs; } ;
struct msm_gpu {int nr_rings; struct msm_ringbuffer** rb; } ;
struct TYPE_2__ {scalar_t__ rptr; } ;

/* Variables and functions */
 scalar_t__ get_wptr (struct msm_ringbuffer*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static struct msm_ringbuffer *get_next_ring(struct msm_gpu *gpu)
{
	unsigned long flags;
	int i;

	for (i = 0; i < gpu->nr_rings; i++) {
		bool empty;
		struct msm_ringbuffer *ring = gpu->rb[i];

		spin_lock_irqsave(&ring->lock, flags);
		empty = (get_wptr(ring) == ring->memptrs->rptr);
		spin_unlock_irqrestore(&ring->lock, flags);

		if (!empty)
			return ring;
	}

	return NULL;
}