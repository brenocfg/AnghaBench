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
struct timer_list {int dummy; } ;
struct msm_gpu {int /*<<< orphan*/  recover_work; int /*<<< orphan*/  name; struct drm_device* dev; } ;
struct msm_drm_private {int /*<<< orphan*/  wq; } ;
struct drm_device {int /*<<< orphan*/  dev; struct msm_drm_private* dev_private; } ;
struct TYPE_2__ {struct msm_gpu base; } ;
struct a5xx_gpu {TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PREEMPT_FAULTED ; 
 int /*<<< orphan*/  PREEMPT_TRIGGERED ; 
 struct a5xx_gpu* a5xx_gpu ; 
 struct a5xx_gpu* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  preempt_timer ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  try_preempt_state (struct a5xx_gpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void a5xx_preempt_timer(struct timer_list *t)
{
	struct a5xx_gpu *a5xx_gpu = from_timer(a5xx_gpu, t, preempt_timer);
	struct msm_gpu *gpu = &a5xx_gpu->base.base;
	struct drm_device *dev = gpu->dev;
	struct msm_drm_private *priv = dev->dev_private;

	if (!try_preempt_state(a5xx_gpu, PREEMPT_TRIGGERED, PREEMPT_FAULTED))
		return;

	DRM_DEV_ERROR(dev->dev, "%s: preemption timed out\n", gpu->name);
	queue_work(priv->wq, &gpu->recover_work);
}