#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct drm_modeset_acquire_ctx {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  flags; } ;
struct TYPE_9__ {TYPE_1__ reset; } ;
struct TYPE_7__ {int /*<<< orphan*/  pending_fb_pin; } ;
struct TYPE_8__ {int /*<<< orphan*/  mutex; } ;
struct drm_device {TYPE_3__ mode_config; } ;
struct drm_i915_private {struct drm_atomic_state* modeset_restore_state; TYPE_4__ gt; TYPE_2__ gpu_error; struct drm_modeset_acquire_ctx reset_ctx; struct drm_device drm; } ;
struct drm_atomic_state {struct drm_modeset_acquire_ctx* acquire_ctx; } ;
struct TYPE_10__ {int /*<<< orphan*/  force_reset_modeset_test; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int EDEADLK ; 
 int /*<<< orphan*/  I915_RESET_MODESET ; 
 scalar_t__ IS_ERR (struct drm_atomic_state*) ; 
 int PTR_ERR (struct drm_atomic_state*) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int drm_atomic_helper_disable_all (struct drm_device*,struct drm_modeset_acquire_ctx*) ; 
 struct drm_atomic_state* drm_atomic_helper_duplicate_state (struct drm_device*,struct drm_modeset_acquire_ctx*) ; 
 int /*<<< orphan*/  drm_atomic_state_put (struct drm_atomic_state*) ; 
 int /*<<< orphan*/  drm_modeset_acquire_init (struct drm_modeset_acquire_ctx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_modeset_backoff (struct drm_modeset_acquire_ctx*) ; 
 int drm_modeset_lock_all_ctx (struct drm_device*,struct drm_modeset_acquire_ctx*) ; 
 int /*<<< orphan*/  gpu_reset_clobbers_display (struct drm_i915_private*) ; 
 TYPE_5__ i915_modparams ; 
 int /*<<< orphan*/  intel_gt_set_wedged (TYPE_4__*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_mb__after_atomic () ; 
 int /*<<< orphan*/  wake_up_bit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void intel_prepare_reset(struct drm_i915_private *dev_priv)
{
	struct drm_device *dev = &dev_priv->drm;
	struct drm_modeset_acquire_ctx *ctx = &dev_priv->reset_ctx;
	struct drm_atomic_state *state;
	int ret;

	/* reset doesn't touch the display */
	if (!i915_modparams.force_reset_modeset_test &&
	    !gpu_reset_clobbers_display(dev_priv))
		return;

	/* We have a modeset vs reset deadlock, defensively unbreak it. */
	set_bit(I915_RESET_MODESET, &dev_priv->gt.reset.flags);
	smp_mb__after_atomic();
	wake_up_bit(&dev_priv->gt.reset.flags, I915_RESET_MODESET);

	if (atomic_read(&dev_priv->gpu_error.pending_fb_pin)) {
		DRM_DEBUG_KMS("Modeset potentially stuck, unbreaking through wedging\n");
		intel_gt_set_wedged(&dev_priv->gt);
	}

	/*
	 * Need mode_config.mutex so that we don't
	 * trample ongoing ->detect() and whatnot.
	 */
	mutex_lock(&dev->mode_config.mutex);
	drm_modeset_acquire_init(ctx, 0);
	while (1) {
		ret = drm_modeset_lock_all_ctx(dev, ctx);
		if (ret != -EDEADLK)
			break;

		drm_modeset_backoff(ctx);
	}
	/*
	 * Disabling the crtcs gracefully seems nicer. Also the
	 * g33 docs say we should at least disable all the planes.
	 */
	state = drm_atomic_helper_duplicate_state(dev, ctx);
	if (IS_ERR(state)) {
		ret = PTR_ERR(state);
		DRM_ERROR("Duplicating state failed with %i\n", ret);
		return;
	}

	ret = drm_atomic_helper_disable_all(dev, ctx);
	if (ret) {
		DRM_ERROR("Suspending crtc's failed with %i\n", ret);
		drm_atomic_state_put(state);
		return;
	}

	dev_priv->modeset_restore_state = state;
	state->acquire_ctx = ctx;
}