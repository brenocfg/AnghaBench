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
struct drm_hdmi_info {int y420_dc_modes; } ;
struct TYPE_2__ {struct drm_hdmi_info hdmi; } ;
struct drm_connector {TYPE_1__ display_info; } ;

/* Variables and functions */
 int const DRM_EDID_YCBCR420_DC_MASK ; 

__attribute__((used)) static void drm_parse_ycbcr420_deep_color_info(struct drm_connector *connector,
					       const u8 *db)
{
	u8 dc_mask;
	struct drm_hdmi_info *hdmi = &connector->display_info.hdmi;

	dc_mask = db[7] & DRM_EDID_YCBCR420_DC_MASK;
	hdmi->y420_dc_modes = dc_mask;
}