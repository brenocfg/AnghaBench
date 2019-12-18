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
struct TYPE_6__ {int /*<<< orphan*/  connection_mutex; } ;
struct TYPE_8__ {TYPE_2__ mode_config; } ;
struct drm_i915_private {TYPE_4__ drm; } ;
struct drm_atomic_state {struct drm_modeset_acquire_ctx* acquire_ctx; } ;
struct TYPE_5__ {int force_min_cdclk_changed; int force_min_cdclk; } ;
struct TYPE_7__ {TYPE_1__ cdclk; } ;

/* Variables and functions */
 int EDEADLK ; 
 scalar_t__ WARN_ON (int) ; 
 int drm_atomic_commit (struct drm_atomic_state*) ; 
 struct drm_atomic_state* drm_atomic_state_alloc (TYPE_4__*) ; 
 int /*<<< orphan*/  drm_atomic_state_clear (struct drm_atomic_state*) ; 
 int /*<<< orphan*/  drm_atomic_state_put (struct drm_atomic_state*) ; 
 int /*<<< orphan*/  drm_modeset_acquire_fini (struct drm_modeset_acquire_ctx*) ; 
 int /*<<< orphan*/  drm_modeset_acquire_init (struct drm_modeset_acquire_ctx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_modeset_backoff (struct drm_modeset_acquire_ctx*) ; 
 int /*<<< orphan*/  drm_modeset_drop_locks (struct drm_modeset_acquire_ctx*) ; 
 int drm_modeset_lock (int /*<<< orphan*/ *,struct drm_modeset_acquire_ctx*) ; 
 TYPE_3__* to_intel_atomic_state (struct drm_atomic_state*) ; 

__attribute__((used)) static void glk_force_audio_cdclk(struct drm_i915_private *dev_priv,
				  bool enable)
{
	struct drm_modeset_acquire_ctx ctx;
	struct drm_atomic_state *state;
	int ret;

	drm_modeset_acquire_init(&ctx, 0);
	state = drm_atomic_state_alloc(&dev_priv->drm);
	if (WARN_ON(!state))
		return;

	state->acquire_ctx = &ctx;

retry:
	to_intel_atomic_state(state)->cdclk.force_min_cdclk_changed = true;
	to_intel_atomic_state(state)->cdclk.force_min_cdclk =
		enable ? 2 * 96000 : 0;

	/*
	 * Protects dev_priv->cdclk.force_min_cdclk
	 * Need to lock this here in case we have no active pipes
	 * and thus wouldn't lock it during the commit otherwise.
	 */
	ret = drm_modeset_lock(&dev_priv->drm.mode_config.connection_mutex,
			       &ctx);
	if (!ret)
		ret = drm_atomic_commit(state);

	if (ret == -EDEADLK) {
		drm_atomic_state_clear(state);
		drm_modeset_backoff(&ctx);
		goto retry;
	}

	WARN_ON(ret);

	drm_atomic_state_put(state);

	drm_modeset_drop_locks(&ctx);
	drm_modeset_acquire_fini(&ctx);
}