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
struct TYPE_4__ {int connectors_changed; } ;
struct TYPE_3__ {int force_thru; int enabled; } ;
struct intel_crtc_state {int ips_force_disable; scalar_t__ cpu_transcoder; TYPE_2__ base; TYPE_1__ pch_pfit; } ;
struct intel_crtc {int dummy; } ;
struct drm_modeset_acquire_ctx {int dummy; } ;
struct drm_device {int dummy; } ;
struct drm_i915_private {struct drm_device drm; } ;
struct drm_atomic_state {struct drm_modeset_acquire_ctx* acquire_ctx; } ;

/* Variables and functions */
 int EDEADLK ; 
 int ENOMEM ; 
 scalar_t__ HAS_IPS (struct drm_i915_private*) ; 
 scalar_t__ IS_ERR (struct intel_crtc_state*) ; 
 scalar_t__ IS_HASWELL (struct drm_i915_private*) ; 
 int /*<<< orphan*/  PIPE_A ; 
 int PTR_ERR (struct intel_crtc_state*) ; 
 scalar_t__ TRANSCODER_EDP ; 
 int /*<<< orphan*/  WARN (int,char*,int,int) ; 
 int drm_atomic_commit (struct drm_atomic_state*) ; 
 struct drm_atomic_state* drm_atomic_state_alloc (struct drm_device*) ; 
 int /*<<< orphan*/  drm_atomic_state_clear (struct drm_atomic_state*) ; 
 int /*<<< orphan*/  drm_atomic_state_put (struct drm_atomic_state*) ; 
 int /*<<< orphan*/  drm_modeset_acquire_fini (struct drm_modeset_acquire_ctx*) ; 
 int /*<<< orphan*/  drm_modeset_acquire_init (struct drm_modeset_acquire_ctx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_modeset_backoff (struct drm_modeset_acquire_ctx*) ; 
 int /*<<< orphan*/  drm_modeset_drop_locks (struct drm_modeset_acquire_ctx*) ; 
 struct intel_crtc_state* intel_atomic_get_crtc_state (struct drm_atomic_state*,struct intel_crtc*) ; 
 struct intel_crtc* intel_get_crtc_for_pipe (struct drm_i915_private*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hsw_pipe_A_crc_wa(struct drm_i915_private *dev_priv,
			      bool enable)
{
	struct drm_device *dev = &dev_priv->drm;
	struct intel_crtc *crtc = intel_get_crtc_for_pipe(dev_priv, PIPE_A);
	struct intel_crtc_state *pipe_config;
	struct drm_atomic_state *state;
	struct drm_modeset_acquire_ctx ctx;
	int ret = 0;

	drm_modeset_acquire_init(&ctx, 0);

	state = drm_atomic_state_alloc(dev);
	if (!state) {
		ret = -ENOMEM;
		goto unlock;
	}

	state->acquire_ctx = &ctx;

retry:
	pipe_config = intel_atomic_get_crtc_state(state, crtc);
	if (IS_ERR(pipe_config)) {
		ret = PTR_ERR(pipe_config);
		goto put_state;
	}

	if (HAS_IPS(dev_priv)) {
		/*
		 * When IPS gets enabled, the pipe CRC changes. Since IPS gets
		 * enabled and disabled dynamically based on package C states,
		 * user space can't make reliable use of the CRCs, so let's just
		 * completely disable it.
		 */
		pipe_config->ips_force_disable = enable;
	}

	if (IS_HASWELL(dev_priv)) {
		pipe_config->pch_pfit.force_thru = enable;
		if (pipe_config->cpu_transcoder == TRANSCODER_EDP &&
		    pipe_config->pch_pfit.enabled != enable)
			pipe_config->base.connectors_changed = true;
	}

	ret = drm_atomic_commit(state);

put_state:
	if (ret == -EDEADLK) {
		drm_atomic_state_clear(state);
		drm_modeset_backoff(&ctx);
		goto retry;
	}

	drm_atomic_state_put(state);
unlock:
	WARN(ret, "Toggling workaround to %i returns %i\n", enable, ret);
	drm_modeset_drop_locks(&ctx);
	drm_modeset_acquire_fini(&ctx);
}