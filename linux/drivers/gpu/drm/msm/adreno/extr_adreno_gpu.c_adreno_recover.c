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
struct msm_gpu {TYPE_1__* funcs; struct drm_device* dev; } ;
struct drm_device {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* pm_resume ) (struct msm_gpu*) ;int /*<<< orphan*/  (* pm_suspend ) (struct msm_gpu*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ ,char*,int) ; 
 int msm_gpu_hw_init (struct msm_gpu*) ; 
 int /*<<< orphan*/  stub1 (struct msm_gpu*) ; 
 int /*<<< orphan*/  stub2 (struct msm_gpu*) ; 

void adreno_recover(struct msm_gpu *gpu)
{
	struct drm_device *dev = gpu->dev;
	int ret;

	// XXX pm-runtime??  we *need* the device to be off after this
	// so maybe continuing to call ->pm_suspend/resume() is better?

	gpu->funcs->pm_suspend(gpu);
	gpu->funcs->pm_resume(gpu);

	ret = msm_gpu_hw_init(gpu);
	if (ret) {
		DRM_DEV_ERROR(dev->dev, "gpu hw init failed: %d\n", ret);
		/* hmm, oh well? */
	}
}