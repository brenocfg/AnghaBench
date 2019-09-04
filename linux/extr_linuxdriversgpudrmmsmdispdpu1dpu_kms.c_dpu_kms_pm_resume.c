#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  acquire_ctx; } ;
struct drm_device {TYPE_1__ mode_config; } ;
struct dpu_kms {int suspend_block; TYPE_2__* suspend_state; } ;
struct device {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  acquire_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPU_ATRACE_BEGIN (char*) ; 
 int /*<<< orphan*/  DPU_ATRACE_END (char*) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int EINVAL ; 
 int /*<<< orphan*/  ddev_to_msm_kms (struct drm_device*) ; 
 struct drm_device* dev_get_drvdata (struct device*) ; 
 int drm_atomic_commit (TYPE_2__*) ; 
 int /*<<< orphan*/  drm_atomic_state_put (TYPE_2__*) ; 
 int /*<<< orphan*/  drm_kms_helper_poll_enable (struct drm_device*) ; 
 int /*<<< orphan*/  drm_mode_config_reset (struct drm_device*) ; 
 int /*<<< orphan*/  drm_modeset_lock_all (struct drm_device*) ; 
 int /*<<< orphan*/  drm_modeset_unlock_all (struct drm_device*) ; 
 struct dpu_kms* to_dpu_kms (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dpu_kms_pm_resume(struct device *dev)
{
	struct drm_device *ddev;
	struct dpu_kms *dpu_kms;
	int ret;

	if (!dev)
		return -EINVAL;

	ddev = dev_get_drvdata(dev);
	if (!ddev || !ddev_to_msm_kms(ddev))
		return -EINVAL;

	dpu_kms = to_dpu_kms(ddev_to_msm_kms(ddev));

	DPU_ATRACE_BEGIN("kms_pm_resume");

	drm_mode_config_reset(ddev);

	drm_modeset_lock_all(ddev);

	dpu_kms->suspend_block = false;

	if (dpu_kms->suspend_state) {
		dpu_kms->suspend_state->acquire_ctx =
			ddev->mode_config.acquire_ctx;
		ret = drm_atomic_commit(dpu_kms->suspend_state);
		if (ret < 0) {
			DRM_ERROR("failed to restore state, %d\n", ret);
			drm_atomic_state_put(dpu_kms->suspend_state);
		}
		dpu_kms->suspend_state = NULL;
	}
	drm_modeset_unlock_all(ddev);

	/* enable hot-plug polling */
	drm_kms_helper_poll_enable(ddev);

	DPU_ATRACE_END("kms_pm_resume");
	return 0;
}