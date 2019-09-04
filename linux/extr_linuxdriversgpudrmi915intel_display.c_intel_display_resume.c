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
struct drm_i915_private {struct drm_atomic_state* modeset_restore_state; } ;
struct drm_device {int dummy; } ;
struct drm_atomic_state {struct drm_modeset_acquire_ctx* acquire_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int EDEADLK ; 
 int __intel_display_resume (struct drm_device*,struct drm_atomic_state*,struct drm_modeset_acquire_ctx*) ; 
 int /*<<< orphan*/  drm_atomic_state_put (struct drm_atomic_state*) ; 
 int /*<<< orphan*/  drm_modeset_acquire_fini (struct drm_modeset_acquire_ctx*) ; 
 int /*<<< orphan*/  drm_modeset_acquire_init (struct drm_modeset_acquire_ctx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_modeset_backoff (struct drm_modeset_acquire_ctx*) ; 
 int /*<<< orphan*/  drm_modeset_drop_locks (struct drm_modeset_acquire_ctx*) ; 
 int drm_modeset_lock_all_ctx (struct drm_device*,struct drm_modeset_acquire_ctx*) ; 
 int /*<<< orphan*/  intel_enable_ipc (struct drm_i915_private*) ; 
 struct drm_i915_private* to_i915 (struct drm_device*) ; 

void intel_display_resume(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = to_i915(dev);
	struct drm_atomic_state *state = dev_priv->modeset_restore_state;
	struct drm_modeset_acquire_ctx ctx;
	int ret;

	dev_priv->modeset_restore_state = NULL;
	if (state)
		state->acquire_ctx = &ctx;

	drm_modeset_acquire_init(&ctx, 0);

	while (1) {
		ret = drm_modeset_lock_all_ctx(dev, &ctx);
		if (ret != -EDEADLK)
			break;

		drm_modeset_backoff(&ctx);
	}

	if (!ret)
		ret = __intel_display_resume(dev, state, &ctx);

	intel_enable_ipc(dev_priv);
	drm_modeset_drop_locks(&ctx);
	drm_modeset_acquire_fini(&ctx);

	if (ret)
		DRM_ERROR("Restoring old state failed with %i\n", ret);
	if (state)
		drm_atomic_state_put(state);
}