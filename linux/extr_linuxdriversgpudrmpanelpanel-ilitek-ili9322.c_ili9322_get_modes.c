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
struct ili9322 {int input; TYPE_2__* conf; } ;
struct drm_panel {int /*<<< orphan*/  drm; struct drm_connector* connector; } ;
struct drm_display_mode {int type; int /*<<< orphan*/  height_mm; int /*<<< orphan*/  width_mm; int /*<<< orphan*/  flags; } ;
struct TYPE_3__ {int /*<<< orphan*/  height_mm; int /*<<< orphan*/  width_mm; int /*<<< orphan*/  name; } ;
struct drm_connector {TYPE_1__ display_info; } ;
struct TYPE_4__ {int /*<<< orphan*/  height_mm; int /*<<< orphan*/  width_mm; scalar_t__ vsync_active_high; scalar_t__ hsync_active_high; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DISPLAY_INFO_LEN ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  DRM_MODE_FLAG_NHSYNC ; 
 int /*<<< orphan*/  DRM_MODE_FLAG_NVSYNC ; 
 int /*<<< orphan*/  DRM_MODE_FLAG_PHSYNC ; 
 int /*<<< orphan*/  DRM_MODE_FLAG_PVSYNC ; 
 int DRM_MODE_TYPE_DRIVER ; 
 int DRM_MODE_TYPE_PREFERRED ; 
 int EINVAL ; 
#define  ILI9322_INPUT_ITU_R_BT656_640X320_YCBCR 135 
#define  ILI9322_INPUT_ITU_R_BT656_720X360_YCBCR 134 
#define  ILI9322_INPUT_PRGB_ALIGNED 133 
#define  ILI9322_INPUT_PRGB_THROUGH 132 
#define  ILI9322_INPUT_SRGB_DUMMY_320X240 131 
#define  ILI9322_INPUT_SRGB_DUMMY_360X240 130 
#define  ILI9322_INPUT_YUV_640X320_YCBCR 129 
#define  ILI9322_INPUT_YUV_720X360_YCBCR 128 
 struct drm_display_mode* drm_mode_duplicate (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_mode_probed_add (struct drm_connector*,struct drm_display_mode*) ; 
 int /*<<< orphan*/  drm_mode_set_name (struct drm_display_mode*) ; 
 int /*<<< orphan*/  itu_r_bt_656_640_mode ; 
 int /*<<< orphan*/  itu_r_bt_656_720_mode ; 
 struct ili9322* panel_to_ili9322 (struct drm_panel*) ; 
 int /*<<< orphan*/  prgb_320x240_mode ; 
 int /*<<< orphan*/  srgb_320x240_mode ; 
 int /*<<< orphan*/  srgb_360x240_mode ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  yuv_640x320_mode ; 
 int /*<<< orphan*/  yuv_720x360_mode ; 

__attribute__((used)) static int ili9322_get_modes(struct drm_panel *panel)
{
	struct drm_connector *connector = panel->connector;
	struct ili9322 *ili = panel_to_ili9322(panel);
	struct drm_display_mode *mode;

	strncpy(connector->display_info.name, "ILI9322 TFT LCD driver\0",
		DRM_DISPLAY_INFO_LEN);
	connector->display_info.width_mm = ili->conf->width_mm;
	connector->display_info.height_mm = ili->conf->height_mm;

	switch (ili->input) {
	case ILI9322_INPUT_SRGB_DUMMY_320X240:
		mode = drm_mode_duplicate(panel->drm, &srgb_320x240_mode);
		break;
	case ILI9322_INPUT_SRGB_DUMMY_360X240:
		mode = drm_mode_duplicate(panel->drm, &srgb_360x240_mode);
		break;
	case ILI9322_INPUT_PRGB_THROUGH:
	case ILI9322_INPUT_PRGB_ALIGNED:
		mode = drm_mode_duplicate(panel->drm, &prgb_320x240_mode);
		break;
	case ILI9322_INPUT_YUV_640X320_YCBCR:
		mode = drm_mode_duplicate(panel->drm, &yuv_640x320_mode);
		break;
	case ILI9322_INPUT_YUV_720X360_YCBCR:
		mode = drm_mode_duplicate(panel->drm, &yuv_720x360_mode);
		break;
	case ILI9322_INPUT_ITU_R_BT656_720X360_YCBCR:
		mode = drm_mode_duplicate(panel->drm, &itu_r_bt_656_720_mode);
		break;
	case ILI9322_INPUT_ITU_R_BT656_640X320_YCBCR:
		mode = drm_mode_duplicate(panel->drm, &itu_r_bt_656_640_mode);
		break;
	default:
		mode = NULL;
		break;
	}
	if (!mode) {
		DRM_ERROR("bad mode or failed to add mode\n");
		return -EINVAL;
	}
	drm_mode_set_name(mode);
	/*
	 * This is the preferred mode because most people are going
	 * to want to use the display with VGA type graphics.
	 */
	mode->type = DRM_MODE_TYPE_DRIVER | DRM_MODE_TYPE_PREFERRED;

	/* Set up the polarity */
	if (ili->conf->hsync_active_high)
		mode->flags |= DRM_MODE_FLAG_PHSYNC;
	else
		mode->flags |= DRM_MODE_FLAG_NHSYNC;
	if (ili->conf->vsync_active_high)
		mode->flags |= DRM_MODE_FLAG_PVSYNC;
	else
		mode->flags |= DRM_MODE_FLAG_NVSYNC;

	mode->width_mm = ili->conf->width_mm;
	mode->height_mm = ili->conf->height_mm;
	drm_mode_probed_add(connector, mode);

	return 1; /* Number of modes */
}