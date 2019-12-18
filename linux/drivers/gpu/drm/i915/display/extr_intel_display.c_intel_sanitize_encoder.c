#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  id; } ;
struct drm_encoder {int /*<<< orphan*/ * crtc; int /*<<< orphan*/  name; TYPE_3__ base; int /*<<< orphan*/  dev; } ;
struct intel_encoder {struct drm_encoder base; int /*<<< orphan*/  (* post_disable ) (struct intel_encoder*,struct intel_crtc_state*,TYPE_5__*) ;int /*<<< orphan*/  (* disable ) (struct intel_encoder*,struct intel_crtc_state*,TYPE_5__*) ;} ;
struct TYPE_8__ {scalar_t__ active; } ;
struct intel_crtc_state {TYPE_2__ base; } ;
struct TYPE_7__ {int /*<<< orphan*/  state; } ;
struct intel_crtc {int /*<<< orphan*/  pipe; TYPE_1__ base; } ;
struct TYPE_10__ {int /*<<< orphan*/ * encoder; int /*<<< orphan*/  dpms; TYPE_5__* state; } ;
struct intel_connector {TYPE_4__ base; } ;
struct drm_i915_private {int dummy; } ;
struct TYPE_11__ {struct drm_encoder* best_encoder; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  DRM_MODE_DPMS_OFF ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ has_bogus_dpll_config (struct intel_crtc_state*) ; 
 int /*<<< orphan*/  icl_sanitize_encoder_pll_mapping (struct intel_encoder*) ; 
 struct intel_connector* intel_encoder_find_connector (struct intel_encoder*) ; 
 int /*<<< orphan*/  intel_opregion_notify_encoder (struct intel_encoder*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pipe_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct intel_encoder*,struct intel_crtc_state*,TYPE_5__*) ; 
 int /*<<< orphan*/  stub2 (struct intel_encoder*,struct intel_crtc_state*,TYPE_5__*) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 
 struct intel_crtc* to_intel_crtc (int /*<<< orphan*/ *) ; 
 struct intel_crtc_state* to_intel_crtc_state (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void intel_sanitize_encoder(struct intel_encoder *encoder)
{
	struct drm_i915_private *dev_priv = to_i915(encoder->base.dev);
	struct intel_connector *connector;
	struct intel_crtc *crtc = to_intel_crtc(encoder->base.crtc);
	struct intel_crtc_state *crtc_state = crtc ?
		to_intel_crtc_state(crtc->base.state) : NULL;

	/* We need to check both for a crtc link (meaning that the
	 * encoder is active and trying to read from a pipe) and the
	 * pipe itself being active. */
	bool has_active_crtc = crtc_state &&
		crtc_state->base.active;

	if (crtc_state && has_bogus_dpll_config(crtc_state)) {
		DRM_DEBUG_KMS("BIOS has misprogrammed the hardware. Disabling pipe %c\n",
			      pipe_name(crtc->pipe));
		has_active_crtc = false;
	}

	connector = intel_encoder_find_connector(encoder);
	if (connector && !has_active_crtc) {
		DRM_DEBUG_KMS("[ENCODER:%d:%s] has active connectors but no active pipe!\n",
			      encoder->base.base.id,
			      encoder->base.name);

		/* Connector is active, but has no active pipe. This is
		 * fallout from our resume register restoring. Disable
		 * the encoder manually again. */
		if (crtc_state) {
			struct drm_encoder *best_encoder;

			DRM_DEBUG_KMS("[ENCODER:%d:%s] manually disabled\n",
				      encoder->base.base.id,
				      encoder->base.name);

			/* avoid oopsing in case the hooks consult best_encoder */
			best_encoder = connector->base.state->best_encoder;
			connector->base.state->best_encoder = &encoder->base;

			if (encoder->disable)
				encoder->disable(encoder, crtc_state,
						 connector->base.state);
			if (encoder->post_disable)
				encoder->post_disable(encoder, crtc_state,
						      connector->base.state);

			connector->base.state->best_encoder = best_encoder;
		}
		encoder->base.crtc = NULL;

		/* Inconsistent output/port/pipe state happens presumably due to
		 * a bug in one of the get_hw_state functions. Or someplace else
		 * in our code, like the register restore mess on resume. Clamp
		 * things to off as a safer default. */

		connector->base.dpms = DRM_MODE_DPMS_OFF;
		connector->base.encoder = NULL;
	}

	/* notify opregion of the sanitized encoder state */
	intel_opregion_notify_encoder(encoder, connector && has_active_crtc);

	if (INTEL_GEN(dev_priv) >= 11)
		icl_sanitize_encoder_pll_mapping(encoder);
}