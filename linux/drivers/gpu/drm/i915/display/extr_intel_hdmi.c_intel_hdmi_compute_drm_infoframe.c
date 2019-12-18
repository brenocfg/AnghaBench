#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct intel_encoder {TYPE_3__ base; } ;
struct hdmi_drm_infoframe {int dummy; } ;
struct TYPE_4__ {struct hdmi_drm_infoframe drm; } ;
struct TYPE_5__ {int /*<<< orphan*/  enable; TYPE_1__ drm; } ;
struct intel_crtc_state {TYPE_2__ infoframes; int /*<<< orphan*/  has_infoframe; } ;
struct drm_i915_private {int dummy; } ;
struct drm_connector_state {int /*<<< orphan*/  hdr_output_metadata; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 int /*<<< orphan*/  HDMI_INFOFRAME_TYPE_DRM ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ IS_GEMINILAKE (struct drm_i915_private*) ; 
 scalar_t__ WARN_ON (int) ; 
 int drm_hdmi_infoframe_set_hdr_metadata (struct hdmi_drm_infoframe*,struct drm_connector_state*) ; 
 int hdmi_drm_infoframe_check (struct hdmi_drm_infoframe*) ; 
 int /*<<< orphan*/  intel_hdmi_infoframe_enable (int /*<<< orphan*/ ) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
intel_hdmi_compute_drm_infoframe(struct intel_encoder *encoder,
				 struct intel_crtc_state *crtc_state,
				 struct drm_connector_state *conn_state)
{
	struct hdmi_drm_infoframe *frame = &crtc_state->infoframes.drm.drm;
	struct drm_i915_private *dev_priv = to_i915(encoder->base.dev);
	int ret;

	if (!(INTEL_GEN(dev_priv) >= 10 || IS_GEMINILAKE(dev_priv)))
		return true;

	if (!crtc_state->has_infoframe)
		return true;

	if (!conn_state->hdr_output_metadata)
		return true;

	crtc_state->infoframes.enable |=
		intel_hdmi_infoframe_enable(HDMI_INFOFRAME_TYPE_DRM);

	ret = drm_hdmi_infoframe_set_hdr_metadata(frame, conn_state);
	if (ret < 0) {
		DRM_DEBUG_KMS("couldn't set HDR metadata in infoframe\n");
		return false;
	}

	ret = hdmi_drm_infoframe_check(frame);
	if (WARN_ON(ret))
		return false;

	return true;
}