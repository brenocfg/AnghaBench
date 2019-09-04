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
typedef  int u8 ;
typedef  int u32 ;
struct TYPE_2__ {int supported; int low_rates; } ;
struct drm_scdc {int supported; int read_request; TYPE_1__ scrambling; } ;
struct drm_hdmi_info {struct drm_scdc scdc; } ;
struct drm_display_info {int has_hdmi_infoframe; int max_tmds_clock; struct drm_hdmi_info hdmi; } ;
struct drm_connector {struct drm_display_info display_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int) ; 
 int /*<<< orphan*/  drm_parse_ycbcr420_deep_color_info (struct drm_connector*,int const*) ; 

__attribute__((used)) static void drm_parse_hdmi_forum_vsdb(struct drm_connector *connector,
				 const u8 *hf_vsdb)
{
	struct drm_display_info *display = &connector->display_info;
	struct drm_hdmi_info *hdmi = &display->hdmi;

	display->has_hdmi_infoframe = true;

	if (hf_vsdb[6] & 0x80) {
		hdmi->scdc.supported = true;
		if (hf_vsdb[6] & 0x40)
			hdmi->scdc.read_request = true;
	}

	/*
	 * All HDMI 2.0 monitors must support scrambling at rates > 340 MHz.
	 * And as per the spec, three factors confirm this:
	 * * Availability of a HF-VSDB block in EDID (check)
	 * * Non zero Max_TMDS_Char_Rate filed in HF-VSDB (let's check)
	 * * SCDC support available (let's check)
	 * Lets check it out.
	 */

	if (hf_vsdb[5]) {
		/* max clock is 5000 KHz times block value */
		u32 max_tmds_clock = hf_vsdb[5] * 5000;
		struct drm_scdc *scdc = &hdmi->scdc;

		if (max_tmds_clock > 340000) {
			display->max_tmds_clock = max_tmds_clock;
			DRM_DEBUG_KMS("HF-VSDB: max TMDS clock %d kHz\n",
				display->max_tmds_clock);
		}

		if (scdc->supported) {
			scdc->scrambling.supported = true;

			/* Few sinks support scrambling for cloks < 340M */
			if ((hf_vsdb[6] & 0x8))
				scdc->scrambling.low_rates = true;
		}
	}

	drm_parse_ycbcr420_deep_color_info(connector, hf_vsdb);
}