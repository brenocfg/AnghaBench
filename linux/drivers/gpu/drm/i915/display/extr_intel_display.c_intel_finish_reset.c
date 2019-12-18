#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct drm_modeset_acquire_ctx {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  flags; } ;
struct TYPE_8__ {TYPE_3__ reset; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* hpd_irq_setup ) (struct drm_i915_private*) ;} ;
struct TYPE_6__ {int /*<<< orphan*/  mutex; } ;
struct drm_device {TYPE_2__ mode_config; } ;
struct drm_i915_private {TYPE_4__ gt; int /*<<< orphan*/  irq_lock; TYPE_1__ display; int /*<<< orphan*/  modeset_restore_state; struct drm_modeset_acquire_ctx reset_ctx; struct drm_device drm; } ;
struct drm_atomic_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int /*<<< orphan*/  I915_RESET_MODESET ; 
 int __intel_display_resume (struct drm_device*,struct drm_atomic_state*,struct drm_modeset_acquire_ctx*) ; 
 int /*<<< orphan*/  clear_bit_unlock (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_atomic_state_put (struct drm_atomic_state*) ; 
 int /*<<< orphan*/  drm_modeset_acquire_fini (struct drm_modeset_acquire_ctx*) ; 
 int /*<<< orphan*/  drm_modeset_drop_locks (struct drm_modeset_acquire_ctx*) ; 
 struct drm_atomic_state* fetch_and_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gpu_reset_clobbers_display (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_hpd_init (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_init_clock_gating (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_modeset_init_hw (struct drm_device*) ; 
 int /*<<< orphan*/  intel_pps_unlock_regs_wa (struct drm_i915_private*) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct drm_i915_private*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void intel_finish_reset(struct drm_i915_private *dev_priv)
{
	struct drm_device *dev = &dev_priv->drm;
	struct drm_modeset_acquire_ctx *ctx = &dev_priv->reset_ctx;
	struct drm_atomic_state *state;
	int ret;

	/* reset doesn't touch the display */
	if (!test_bit(I915_RESET_MODESET, &dev_priv->gt.reset.flags))
		return;

	state = fetch_and_zero(&dev_priv->modeset_restore_state);
	if (!state)
		goto unlock;

	/* reset doesn't touch the display */
	if (!gpu_reset_clobbers_display(dev_priv)) {
		/* for testing only restore the display */
		ret = __intel_display_resume(dev, state, ctx);
		if (ret)
			DRM_ERROR("Restoring old state failed with %i\n", ret);
	} else {
		/*
		 * The display has been reset as well,
		 * so need a full re-initialization.
		 */
		intel_pps_unlock_regs_wa(dev_priv);
		intel_modeset_init_hw(dev);
		intel_init_clock_gating(dev_priv);

		spin_lock_irq(&dev_priv->irq_lock);
		if (dev_priv->display.hpd_irq_setup)
			dev_priv->display.hpd_irq_setup(dev_priv);
		spin_unlock_irq(&dev_priv->irq_lock);

		ret = __intel_display_resume(dev, state, ctx);
		if (ret)
			DRM_ERROR("Restoring old state failed with %i\n", ret);

		intel_hpd_init(dev_priv);
	}

	drm_atomic_state_put(state);
unlock:
	drm_modeset_drop_locks(ctx);
	drm_modeset_acquire_fini(ctx);
	mutex_unlock(&dev->mode_config.mutex);

	clear_bit_unlock(I915_RESET_MODESET, &dev_priv->gt.reset.flags);
}