#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct intel_encoder {int dummy; } ;
struct intel_crtc_state {scalar_t__ has_audio; } ;
struct drm_connector_state {struct drm_connector* connector; } ;
struct TYPE_2__ {int /*<<< orphan*/  id; } ;
struct drm_connector {int /*<<< orphan*/  name; TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_audio_codec_disable (struct intel_encoder*,struct intel_crtc_state const*,struct drm_connector_state const*) ; 
 int /*<<< orphan*/  intel_hdmi_handle_sink_scrambling (struct intel_encoder*,struct drm_connector*,int,int) ; 

__attribute__((used)) static void intel_disable_ddi_hdmi(struct intel_encoder *encoder,
				   const struct intel_crtc_state *old_crtc_state,
				   const struct drm_connector_state *old_conn_state)
{
	struct drm_connector *connector = old_conn_state->connector;

	if (old_crtc_state->has_audio)
		intel_audio_codec_disable(encoder,
					  old_crtc_state, old_conn_state);

	if (!intel_hdmi_handle_sink_scrambling(encoder, connector,
					       false, false))
		DRM_DEBUG_KMS("[CONNECTOR:%d:%s] Failed to reset sink scrambling/TMDS bit clock ratio\n",
			      connector->base.id, connector->name);
}