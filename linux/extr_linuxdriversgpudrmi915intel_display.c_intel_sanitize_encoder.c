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
struct TYPE_6__ {int /*<<< orphan*/  id; } ;
struct TYPE_7__ {TYPE_5__* crtc; int /*<<< orphan*/  name; TYPE_1__ base; } ;
struct intel_encoder {TYPE_2__ base; int /*<<< orphan*/  (* post_disable ) (struct intel_encoder*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* disable ) (struct intel_encoder*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_8__ {int /*<<< orphan*/ * encoder; int /*<<< orphan*/  dpms; int /*<<< orphan*/  state; } ;
struct intel_connector {TYPE_3__ base; } ;
struct drm_crtc_state {int dummy; } ;
struct TYPE_10__ {struct drm_crtc_state* state; } ;
struct TYPE_9__ {scalar_t__ active; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRM_MODE_DPMS_OFF ; 
 struct intel_connector* intel_encoder_find_connector (struct intel_encoder*) ; 
 int /*<<< orphan*/  intel_opregion_notify_encoder (struct intel_encoder*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct intel_encoder*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct intel_encoder*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__* to_intel_crtc (TYPE_5__*) ; 
 int /*<<< orphan*/  to_intel_crtc_state (struct drm_crtc_state*) ; 

__attribute__((used)) static void intel_sanitize_encoder(struct intel_encoder *encoder)
{
	struct intel_connector *connector;

	/* We need to check both for a crtc link (meaning that the
	 * encoder is active and trying to read from a pipe) and the
	 * pipe itself being active. */
	bool has_active_crtc = encoder->base.crtc &&
		to_intel_crtc(encoder->base.crtc)->active;

	connector = intel_encoder_find_connector(encoder);
	if (connector && !has_active_crtc) {
		DRM_DEBUG_KMS("[ENCODER:%d:%s] has active connectors but no active pipe!\n",
			      encoder->base.base.id,
			      encoder->base.name);

		/* Connector is active, but has no active pipe. This is
		 * fallout from our resume register restoring. Disable
		 * the encoder manually again. */
		if (encoder->base.crtc) {
			struct drm_crtc_state *crtc_state = encoder->base.crtc->state;

			DRM_DEBUG_KMS("[ENCODER:%d:%s] manually disabled\n",
				      encoder->base.base.id,
				      encoder->base.name);
			encoder->disable(encoder, to_intel_crtc_state(crtc_state), connector->base.state);
			if (encoder->post_disable)
				encoder->post_disable(encoder, to_intel_crtc_state(crtc_state), connector->base.state);
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
}