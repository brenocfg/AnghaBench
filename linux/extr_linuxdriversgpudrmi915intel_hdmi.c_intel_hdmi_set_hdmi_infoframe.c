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
struct TYPE_3__ {int /*<<< orphan*/  hdmi; } ;
union hdmi_infoframe {TYPE_1__ vendor; } ;
struct TYPE_4__ {int /*<<< orphan*/  adjusted_mode; } ;
struct intel_crtc_state {TYPE_2__ base; } ;
struct drm_encoder {int dummy; } ;
struct drm_connector_state {int /*<<< orphan*/  connector; } ;

/* Variables and functions */
 int drm_hdmi_vendor_infoframe_from_display_mode (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_write_infoframe (struct drm_encoder*,struct intel_crtc_state const*,union hdmi_infoframe*) ; 

__attribute__((used)) static void
intel_hdmi_set_hdmi_infoframe(struct drm_encoder *encoder,
			      const struct intel_crtc_state *crtc_state,
			      const struct drm_connector_state *conn_state)
{
	union hdmi_infoframe frame;
	int ret;

	ret = drm_hdmi_vendor_infoframe_from_display_mode(&frame.vendor.hdmi,
							  conn_state->connector,
							  &crtc_state->base.adjusted_mode);
	if (ret < 0)
		return;

	intel_write_infoframe(encoder, crtc_state, &frame);
}