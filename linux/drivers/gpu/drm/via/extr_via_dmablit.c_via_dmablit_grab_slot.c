#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ num_free; int /*<<< orphan*/  blit_lock; int /*<<< orphan*/  busy_queue; } ;
typedef  TYPE_1__ drm_via_blitq_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*,scalar_t__) ; 
 int EAGAIN ; 
 int EINTR ; 
 int /*<<< orphan*/  HZ ; 
 int /*<<< orphan*/  VIA_WAIT_ON (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int
via_dmablit_grab_slot(drm_via_blitq_t *blitq, int engine)
{
	int ret = 0;
	unsigned long irqsave;

	DRM_DEBUG("Num free is %d\n", blitq->num_free);
	spin_lock_irqsave(&blitq->blit_lock, irqsave);
	while (blitq->num_free == 0) {
		spin_unlock_irqrestore(&blitq->blit_lock, irqsave);

		VIA_WAIT_ON(ret, blitq->busy_queue, HZ, blitq->num_free > 0);
		if (ret)
			return (-EINTR == ret) ? -EAGAIN : ret;

		spin_lock_irqsave(&blitq->blit_lock, irqsave);
	}

	blitq->num_free--;
	spin_unlock_irqrestore(&blitq->blit_lock, irqsave);

	return 0;
}