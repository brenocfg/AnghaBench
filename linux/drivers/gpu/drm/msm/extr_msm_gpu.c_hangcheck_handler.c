#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct timer_list {int dummy; } ;
struct msm_ringbuffer {scalar_t__ hangcheck_fence; scalar_t__ seqno; scalar_t__ id; TYPE_2__* memptrs; } ;
struct msm_gpu {int /*<<< orphan*/  retire_work; int /*<<< orphan*/  recover_work; int /*<<< orphan*/  name; TYPE_1__* funcs; struct drm_device* dev; } ;
struct msm_drm_private {int /*<<< orphan*/  wq; } ;
struct drm_device {int /*<<< orphan*/  dev; struct msm_drm_private* dev_private; } ;
struct TYPE_4__ {scalar_t__ fence; } ;
struct TYPE_3__ {struct msm_ringbuffer* (* active_ring ) (struct msm_gpu*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 struct msm_gpu* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 struct msm_gpu* gpu ; 
 int /*<<< orphan*/  hangcheck_timer ; 
 int /*<<< orphan*/  hangcheck_timer_reset (struct msm_gpu*) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct msm_ringbuffer* stub1 (struct msm_gpu*) ; 

__attribute__((used)) static void hangcheck_handler(struct timer_list *t)
{
	struct msm_gpu *gpu = from_timer(gpu, t, hangcheck_timer);
	struct drm_device *dev = gpu->dev;
	struct msm_drm_private *priv = dev->dev_private;
	struct msm_ringbuffer *ring = gpu->funcs->active_ring(gpu);
	uint32_t fence = ring->memptrs->fence;

	if (fence != ring->hangcheck_fence) {
		/* some progress has been made.. ya! */
		ring->hangcheck_fence = fence;
	} else if (fence < ring->seqno) {
		/* no progress and not done.. hung! */
		ring->hangcheck_fence = fence;
		DRM_DEV_ERROR(dev->dev, "%s: hangcheck detected gpu lockup rb %d!\n",
				gpu->name, ring->id);
		DRM_DEV_ERROR(dev->dev, "%s:     completed fence: %u\n",
				gpu->name, fence);
		DRM_DEV_ERROR(dev->dev, "%s:     submitted fence: %u\n",
				gpu->name, ring->seqno);

		queue_work(priv->wq, &gpu->recover_work);
	}

	/* if still more pending work, reset the hangcheck timer: */
	if (ring->seqno > ring->hangcheck_fence)
		hangcheck_timer_reset(gpu);

	/* workaround for missing irq: */
	queue_work(priv->wq, &gpu->retire_work);
}