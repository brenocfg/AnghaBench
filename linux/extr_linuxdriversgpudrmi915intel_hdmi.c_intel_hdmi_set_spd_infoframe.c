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
struct TYPE_2__ {int /*<<< orphan*/  sdi; } ;
union hdmi_infoframe {TYPE_1__ spd; } ;
struct intel_crtc_state {int dummy; } ;
struct drm_encoder {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  HDMI_SPD_SDI_PC ; 
 int hdmi_spd_infoframe_init (TYPE_1__*,char*,char*) ; 
 int /*<<< orphan*/  intel_write_infoframe (struct drm_encoder*,struct intel_crtc_state const*,union hdmi_infoframe*) ; 

__attribute__((used)) static void intel_hdmi_set_spd_infoframe(struct drm_encoder *encoder,
					 const struct intel_crtc_state *crtc_state)
{
	union hdmi_infoframe frame;
	int ret;

	ret = hdmi_spd_infoframe_init(&frame.spd, "Intel", "Integrated gfx");
	if (ret < 0) {
		DRM_ERROR("couldn't fill SPD infoframe\n");
		return;
	}

	frame.spd.sdi = HDMI_SPD_SDI_PC;

	intel_write_infoframe(encoder, crtc_state, &frame);
}