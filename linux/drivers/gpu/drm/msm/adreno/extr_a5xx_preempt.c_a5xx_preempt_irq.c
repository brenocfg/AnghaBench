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
struct msm_gpu {int /*<<< orphan*/  recover_work; int /*<<< orphan*/  name; struct drm_device* dev; } ;
struct msm_drm_private {int /*<<< orphan*/  wq; } ;
struct drm_device {int /*<<< orphan*/  dev; struct msm_drm_private* dev_private; } ;
struct adreno_gpu {int dummy; } ;
struct a5xx_gpu {int /*<<< orphan*/ * cur_ring; int /*<<< orphan*/ * next_ring; int /*<<< orphan*/  preempt_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PREEMPT_FAULTED ; 
 int /*<<< orphan*/  PREEMPT_NONE ; 
 int /*<<< orphan*/  PREEMPT_PENDING ; 
 int /*<<< orphan*/  PREEMPT_TRIGGERED ; 
 int /*<<< orphan*/  REG_A5XX_CP_CONTEXT_SWITCH_CNTL ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gpu_read (struct msm_gpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_preempt_state (struct a5xx_gpu*,int /*<<< orphan*/ ) ; 
 struct a5xx_gpu* to_a5xx_gpu (struct adreno_gpu*) ; 
 struct adreno_gpu* to_adreno_gpu (struct msm_gpu*) ; 
 int /*<<< orphan*/  try_preempt_state (struct a5xx_gpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_wptr (struct msm_gpu*,int /*<<< orphan*/ *) ; 

void a5xx_preempt_irq(struct msm_gpu *gpu)
{
	uint32_t status;
	struct adreno_gpu *adreno_gpu = to_adreno_gpu(gpu);
	struct a5xx_gpu *a5xx_gpu = to_a5xx_gpu(adreno_gpu);
	struct drm_device *dev = gpu->dev;
	struct msm_drm_private *priv = dev->dev_private;

	if (!try_preempt_state(a5xx_gpu, PREEMPT_TRIGGERED, PREEMPT_PENDING))
		return;

	/* Delete the preemption watchdog timer */
	del_timer(&a5xx_gpu->preempt_timer);

	/*
	 * The hardware should be setting CP_CONTEXT_SWITCH_CNTL to zero before
	 * firing the interrupt, but there is a non zero chance of a hardware
	 * condition or a software race that could set it again before we have a
	 * chance to finish. If that happens, log and go for recovery
	 */
	status = gpu_read(gpu, REG_A5XX_CP_CONTEXT_SWITCH_CNTL);
	if (unlikely(status)) {
		set_preempt_state(a5xx_gpu, PREEMPT_FAULTED);
		DRM_DEV_ERROR(dev->dev, "%s: Preemption failed to complete\n",
			gpu->name);
		queue_work(priv->wq, &gpu->recover_work);
		return;
	}

	a5xx_gpu->cur_ring = a5xx_gpu->next_ring;
	a5xx_gpu->next_ring = NULL;

	update_wptr(gpu, a5xx_gpu->cur_ring);

	set_preempt_state(a5xx_gpu, PREEMPT_NONE);
}