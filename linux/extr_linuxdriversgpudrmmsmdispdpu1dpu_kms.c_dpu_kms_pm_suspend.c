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
struct drm_modeset_acquire_ctx {int dummy; } ;
struct drm_device {int dummy; } ;
struct drm_atomic_state {struct drm_modeset_acquire_ctx* acquire_ctx; } ;
struct dpu_kms {int suspend_block; struct drm_atomic_state* suspend_state; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPU_ATRACE_BEGIN (char*) ; 
 int /*<<< orphan*/  DPU_ATRACE_END (char*) ; 
 int /*<<< orphan*/  DRM_DEBUG (char*) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 
 int EDEADLK ; 
 int EINVAL ; 
 scalar_t__ IS_ERR_OR_NULL (struct drm_atomic_state*) ; 
 int /*<<< orphan*/  ddev_to_msm_kms (struct drm_device*) ; 
 struct drm_device* dev_get_drvdata (struct device*) ; 
 int drm_atomic_commit (struct drm_atomic_state*) ; 
 struct drm_atomic_state* drm_atomic_helper_duplicate_state (struct drm_device*,struct drm_modeset_acquire_ctx*) ; 
 struct drm_atomic_state* drm_atomic_state_alloc (struct drm_device*) ; 
 int /*<<< orphan*/  drm_atomic_state_put (struct drm_atomic_state*) ; 
 int /*<<< orphan*/  drm_kms_helper_poll_disable (struct drm_device*) ; 
 int /*<<< orphan*/  drm_modeset_acquire_fini (struct drm_modeset_acquire_ctx*) ; 
 int /*<<< orphan*/  drm_modeset_acquire_init (struct drm_modeset_acquire_ctx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_modeset_backoff (struct drm_modeset_acquire_ctx*) ; 
 int /*<<< orphan*/  drm_modeset_drop_locks (struct drm_modeset_acquire_ctx*) ; 
 int drm_modeset_lock_all_ctx (struct drm_device*,struct drm_modeset_acquire_ctx*) ; 
 struct dpu_kms* to_dpu_kms (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dpu_kms_pm_suspend(struct device *dev)
{
	struct drm_device *ddev;
	struct drm_modeset_acquire_ctx ctx;
	struct drm_atomic_state *state;
	struct dpu_kms *dpu_kms;
	int ret = 0, num_crtcs = 0;

	if (!dev)
		return -EINVAL;

	ddev = dev_get_drvdata(dev);
	if (!ddev || !ddev_to_msm_kms(ddev))
		return -EINVAL;

	dpu_kms = to_dpu_kms(ddev_to_msm_kms(ddev));

	/* disable hot-plug polling */
	drm_kms_helper_poll_disable(ddev);

	/* acquire modeset lock(s) */
	drm_modeset_acquire_init(&ctx, 0);

retry:
	DPU_ATRACE_BEGIN("kms_pm_suspend");

	ret = drm_modeset_lock_all_ctx(ddev, &ctx);
	if (ret)
		goto unlock;

	/* save current state for resume */
	if (dpu_kms->suspend_state)
		drm_atomic_state_put(dpu_kms->suspend_state);
	dpu_kms->suspend_state = drm_atomic_helper_duplicate_state(ddev, &ctx);
	if (IS_ERR_OR_NULL(dpu_kms->suspend_state)) {
		DRM_ERROR("failed to back up suspend state\n");
		dpu_kms->suspend_state = NULL;
		goto unlock;
	}

	/* create atomic state to disable all CRTCs */
	state = drm_atomic_state_alloc(ddev);
	if (IS_ERR_OR_NULL(state)) {
		DRM_ERROR("failed to allocate crtc disable state\n");
		goto unlock;
	}

	state->acquire_ctx = &ctx;

	/* check for nothing to do */
	if (num_crtcs == 0) {
		DRM_DEBUG("all crtcs are already in the off state\n");
		drm_atomic_state_put(state);
		goto suspended;
	}

	/* commit the "disable all" state */
	ret = drm_atomic_commit(state);
	if (ret < 0) {
		DRM_ERROR("failed to disable crtcs, %d\n", ret);
		drm_atomic_state_put(state);
		goto unlock;
	}

suspended:
	dpu_kms->suspend_block = true;

unlock:
	if (ret == -EDEADLK) {
		drm_modeset_backoff(&ctx);
		goto retry;
	}
	drm_modeset_drop_locks(&ctx);
	drm_modeset_acquire_fini(&ctx);

	DPU_ATRACE_END("kms_pm_suspend");
	return 0;
}