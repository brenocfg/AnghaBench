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
typedef  size_t u32 ;
struct sti_hda {int /*<<< orphan*/  clk_pix; int /*<<< orphan*/  clk_hddac; int /*<<< orphan*/  mode; } ;
struct drm_display_mode {int clock; } ;
struct drm_bridge {struct sti_hda* driver_private; } ;
struct TYPE_2__ {int vid_cat; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 
#define  VID_ED 129 
#define  VID_HD_74M 128 
 int clk_set_rate (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hda_get_mode_idx (int /*<<< orphan*/ ,size_t*) ; 
 TYPE_1__* hda_supported_modes ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct drm_display_mode const*,int) ; 

__attribute__((used)) static void sti_hda_set_mode(struct drm_bridge *bridge,
			     const struct drm_display_mode *mode,
			     const struct drm_display_mode *adjusted_mode)
{
	struct sti_hda *hda = bridge->driver_private;
	u32 mode_idx;
	int hddac_rate;
	int ret;

	DRM_DEBUG_DRIVER("\n");

	memcpy(&hda->mode, mode, sizeof(struct drm_display_mode));

	if (!hda_get_mode_idx(hda->mode, &mode_idx)) {
		DRM_ERROR("Undefined mode\n");
		return;
	}

	switch (hda_supported_modes[mode_idx].vid_cat) {
	case VID_HD_74M:
		/* HD use alternate 2x filter */
		hddac_rate = mode->clock * 1000 * 2;
		break;
	case VID_ED:
		/* ED uses 4x filter */
		hddac_rate = mode->clock * 1000 * 4;
		break;
	default:
		DRM_ERROR("Undefined mode\n");
		return;
	}

	/* HD DAC = 148.5Mhz or 108 Mhz */
	ret = clk_set_rate(hda->clk_hddac, hddac_rate);
	if (ret < 0)
		DRM_ERROR("Cannot set rate (%dHz) for hda_hddac clk\n",
			  hddac_rate);

	/* HDformatter clock = compositor clock */
	ret = clk_set_rate(hda->clk_pix, mode->clock * 1000);
	if (ret < 0)
		DRM_ERROR("Cannot set rate (%dHz) for hda_pix clk\n",
			  mode->clock * 1000);
}