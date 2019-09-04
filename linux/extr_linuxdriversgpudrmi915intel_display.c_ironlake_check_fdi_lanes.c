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
struct TYPE_3__ {struct drm_atomic_state* state; } ;
struct intel_crtc_state {int fdi_lanes; TYPE_1__ base; } ;
struct intel_crtc {int dummy; } ;
struct drm_i915_private {int dummy; } ;
struct drm_device {int dummy; } ;
struct drm_atomic_state {int dummy; } ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;
struct TYPE_4__ {int num_pipes; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,...) ; 
 int EINVAL ; 
 TYPE_2__* INTEL_INFO (struct drm_i915_private*) ; 
 scalar_t__ IS_BROADWELL (struct drm_i915_private*) ; 
 int /*<<< orphan*/  IS_ERR (struct intel_crtc_state*) ; 
 scalar_t__ IS_HASWELL (struct drm_i915_private*) ; 
#define  PIPE_A 130 
#define  PIPE_B 129 
#define  PIPE_C 128 
 int PTR_ERR (struct intel_crtc_state*) ; 
 struct intel_crtc_state* intel_atomic_get_crtc_state (struct drm_atomic_state*,struct intel_crtc*) ; 
 struct intel_crtc* intel_get_crtc_for_pipe (struct drm_i915_private*,int const) ; 
 int /*<<< orphan*/  pipe_name (int) ; 
 int pipe_required_fdi_lanes (struct intel_crtc_state*) ; 
 struct drm_i915_private* to_i915 (struct drm_device*) ; 

__attribute__((used)) static int ironlake_check_fdi_lanes(struct drm_device *dev, enum pipe pipe,
				     struct intel_crtc_state *pipe_config)
{
	struct drm_i915_private *dev_priv = to_i915(dev);
	struct drm_atomic_state *state = pipe_config->base.state;
	struct intel_crtc *other_crtc;
	struct intel_crtc_state *other_crtc_state;

	DRM_DEBUG_KMS("checking fdi config on pipe %c, lanes %i\n",
		      pipe_name(pipe), pipe_config->fdi_lanes);
	if (pipe_config->fdi_lanes > 4) {
		DRM_DEBUG_KMS("invalid fdi lane config on pipe %c: %i lanes\n",
			      pipe_name(pipe), pipe_config->fdi_lanes);
		return -EINVAL;
	}

	if (IS_HASWELL(dev_priv) || IS_BROADWELL(dev_priv)) {
		if (pipe_config->fdi_lanes > 2) {
			DRM_DEBUG_KMS("only 2 lanes on haswell, required: %i lanes\n",
				      pipe_config->fdi_lanes);
			return -EINVAL;
		} else {
			return 0;
		}
	}

	if (INTEL_INFO(dev_priv)->num_pipes == 2)
		return 0;

	/* Ivybridge 3 pipe is really complicated */
	switch (pipe) {
	case PIPE_A:
		return 0;
	case PIPE_B:
		if (pipe_config->fdi_lanes <= 2)
			return 0;

		other_crtc = intel_get_crtc_for_pipe(dev_priv, PIPE_C);
		other_crtc_state =
			intel_atomic_get_crtc_state(state, other_crtc);
		if (IS_ERR(other_crtc_state))
			return PTR_ERR(other_crtc_state);

		if (pipe_required_fdi_lanes(other_crtc_state) > 0) {
			DRM_DEBUG_KMS("invalid shared fdi lane config on pipe %c: %i lanes\n",
				      pipe_name(pipe), pipe_config->fdi_lanes);
			return -EINVAL;
		}
		return 0;
	case PIPE_C:
		if (pipe_config->fdi_lanes > 2) {
			DRM_DEBUG_KMS("only 2 lanes on pipe %c: required %i lanes\n",
				      pipe_name(pipe), pipe_config->fdi_lanes);
			return -EINVAL;
		}

		other_crtc = intel_get_crtc_for_pipe(dev_priv, PIPE_B);
		other_crtc_state =
			intel_atomic_get_crtc_state(state, other_crtc);
		if (IS_ERR(other_crtc_state))
			return PTR_ERR(other_crtc_state);

		if (pipe_required_fdi_lanes(other_crtc_state) > 2) {
			DRM_DEBUG_KMS("fdi link B uses too many lanes to enable link C\n");
			return -EINVAL;
		}
		return 0;
	default:
		BUG();
	}
}