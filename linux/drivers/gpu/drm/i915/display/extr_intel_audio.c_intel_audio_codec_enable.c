#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  dev; } ;
struct intel_encoder {int port; struct drm_connector* audio_connector; TYPE_1__ base; } ;
struct drm_display_mode {int dummy; } ;
struct TYPE_10__ {struct drm_display_mode adjusted_mode; int /*<<< orphan*/  crtc; } ;
struct intel_crtc_state {int /*<<< orphan*/  port_clock; TYPE_2__ base; } ;
struct intel_crtc {int pipe; } ;
struct TYPE_16__ {TYPE_7__* audio_ops; } ;
struct i915_audio_component {TYPE_8__ base; } ;
struct TYPE_14__ {int /*<<< orphan*/  (* audio_codec_enable ) (struct intel_encoder*,struct intel_crtc_state const*,struct drm_connector_state const*) ;} ;
struct drm_i915_private {int /*<<< orphan*/  av_mutex; struct intel_encoder** av_enc_map; TYPE_6__ display; struct i915_audio_component* audio_component; } ;
struct drm_connector_state {struct drm_connector* connector; } ;
struct TYPE_11__ {int /*<<< orphan*/  id; } ;
struct drm_connector {int* eld; TYPE_5__* encoder; int /*<<< orphan*/  name; TYPE_3__ base; } ;
typedef  enum port { ____Placeholder_port } port ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;
struct TYPE_15__ {int /*<<< orphan*/  audio_ptr; int /*<<< orphan*/  (* pin_eld_notify ) (int /*<<< orphan*/ ,int,int) ;} ;
struct TYPE_12__ {int /*<<< orphan*/  id; } ;
struct TYPE_13__ {int /*<<< orphan*/  name; TYPE_4__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INTEL_OUTPUT_DP_MST ; 
 int drm_av_sync_delay (struct drm_connector*,struct drm_display_mode const*) ; 
 int /*<<< orphan*/  intel_crtc_has_dp_encoder (struct intel_crtc_state const*) ; 
 int /*<<< orphan*/  intel_crtc_has_type (struct intel_crtc_state const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_lpe_audio_notify (struct drm_i915_private*,int,int,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct intel_encoder*,struct intel_crtc_state const*,struct drm_connector_state const*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int,int) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 
 struct intel_crtc* to_intel_crtc (int /*<<< orphan*/ ) ; 

void intel_audio_codec_enable(struct intel_encoder *encoder,
			      const struct intel_crtc_state *crtc_state,
			      const struct drm_connector_state *conn_state)
{
	struct drm_i915_private *dev_priv = to_i915(encoder->base.dev);
	struct i915_audio_component *acomp = dev_priv->audio_component;
	struct intel_crtc *crtc = to_intel_crtc(crtc_state->base.crtc);
	struct drm_connector *connector = conn_state->connector;
	const struct drm_display_mode *adjusted_mode =
		&crtc_state->base.adjusted_mode;
	enum port port = encoder->port;
	enum pipe pipe = crtc->pipe;

	/* FIXME precompute the ELD in .compute_config() */
	if (!connector->eld[0])
		DRM_DEBUG_KMS("Bogus ELD on [CONNECTOR:%d:%s]\n",
			      connector->base.id, connector->name);

	DRM_DEBUG_DRIVER("ELD on [CONNECTOR:%d:%s], [ENCODER:%d:%s]\n",
			 connector->base.id,
			 connector->name,
			 connector->encoder->base.id,
			 connector->encoder->name);

	connector->eld[6] = drm_av_sync_delay(connector, adjusted_mode) / 2;

	if (dev_priv->display.audio_codec_enable)
		dev_priv->display.audio_codec_enable(encoder,
						     crtc_state,
						     conn_state);

	mutex_lock(&dev_priv->av_mutex);
	encoder->audio_connector = connector;

	/* referred in audio callbacks */
	dev_priv->av_enc_map[pipe] = encoder;
	mutex_unlock(&dev_priv->av_mutex);

	if (acomp && acomp->base.audio_ops &&
	    acomp->base.audio_ops->pin_eld_notify) {
		/* audio drivers expect pipe = -1 to indicate Non-MST cases */
		if (!intel_crtc_has_type(crtc_state, INTEL_OUTPUT_DP_MST))
			pipe = -1;
		acomp->base.audio_ops->pin_eld_notify(acomp->base.audio_ops->audio_ptr,
						 (int) port, (int) pipe);
	}

	intel_lpe_audio_notify(dev_priv, pipe, port, connector->eld,
			       crtc_state->port_clock,
			       intel_crtc_has_dp_encoder(crtc_state));
}