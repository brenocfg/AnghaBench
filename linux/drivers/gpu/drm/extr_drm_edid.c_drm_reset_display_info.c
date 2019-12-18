#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct drm_display_info {int dvi_dual; int has_hdmi_infoframe; int rgb_quant_range_selectable; scalar_t__ non_desktop; int /*<<< orphan*/  hdmi; scalar_t__ max_tmds_clock; scalar_t__ cea_rev; scalar_t__ color_formats; scalar_t__ bpc; scalar_t__ height_mm; scalar_t__ width_mm; } ;
struct drm_connector {struct drm_display_info display_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

void
drm_reset_display_info(struct drm_connector *connector)
{
	struct drm_display_info *info = &connector->display_info;

	info->width_mm = 0;
	info->height_mm = 0;

	info->bpc = 0;
	info->color_formats = 0;
	info->cea_rev = 0;
	info->max_tmds_clock = 0;
	info->dvi_dual = false;
	info->has_hdmi_infoframe = false;
	info->rgb_quant_range_selectable = false;
	memset(&info->hdmi, 0, sizeof(info->hdmi));

	info->non_desktop = 0;
}