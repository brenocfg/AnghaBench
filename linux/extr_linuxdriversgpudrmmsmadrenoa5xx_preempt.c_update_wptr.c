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
typedef  int /*<<< orphan*/  uint32_t ;
struct msm_ringbuffer {int /*<<< orphan*/  lock; } ;
struct msm_gpu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_A5XX_CP_RB_WPTR ; 
 int /*<<< orphan*/  get_wptr (struct msm_ringbuffer*) ; 
 int /*<<< orphan*/  gpu_write (struct msm_gpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static inline void update_wptr(struct msm_gpu *gpu, struct msm_ringbuffer *ring)
{
	unsigned long flags;
	uint32_t wptr;

	if (!ring)
		return;

	spin_lock_irqsave(&ring->lock, flags);
	wptr = get_wptr(ring);
	spin_unlock_irqrestore(&ring->lock, flags);

	gpu_write(gpu, REG_A5XX_CP_RB_WPTR, wptr);
}