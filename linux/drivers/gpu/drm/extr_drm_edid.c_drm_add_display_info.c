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
typedef  int u32 ;
struct edid {int width_cm; int height_cm; int revision; int input; int features; } ;
struct drm_display_info {int width_mm; int height_mm; int non_desktop; int bpc; int /*<<< orphan*/  color_formats; } ;
struct drm_connector {int /*<<< orphan*/  name; struct drm_display_info display_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_COLOR_FORMAT_RGB444 ; 
 int /*<<< orphan*/  DRM_COLOR_FORMAT_YCRCB422 ; 
 int /*<<< orphan*/  DRM_COLOR_FORMAT_YCRCB444 ; 
 int /*<<< orphan*/  DRM_DEBUG (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int) ; 
#define  DRM_EDID_DIGITAL_DEPTH_10 134 
#define  DRM_EDID_DIGITAL_DEPTH_12 133 
#define  DRM_EDID_DIGITAL_DEPTH_14 132 
#define  DRM_EDID_DIGITAL_DEPTH_16 131 
#define  DRM_EDID_DIGITAL_DEPTH_6 130 
#define  DRM_EDID_DIGITAL_DEPTH_8 129 
 int DRM_EDID_DIGITAL_DEPTH_MASK ; 
#define  DRM_EDID_DIGITAL_DEPTH_UNDEF 128 
 int DRM_EDID_DIGITAL_DFP_1_X ; 
 int DRM_EDID_FEATURE_RGB_YCRCB422 ; 
 int DRM_EDID_FEATURE_RGB_YCRCB444 ; 
 int DRM_EDID_INPUT_DIGITAL ; 
 int EDID_QUIRK_NON_DESKTOP ; 
 int /*<<< orphan*/  drm_parse_cea_ext (struct drm_connector*,struct edid const*) ; 
 int /*<<< orphan*/  drm_reset_display_info (struct drm_connector*) ; 
 int edid_get_quirks (struct edid const*) ; 

u32 drm_add_display_info(struct drm_connector *connector, const struct edid *edid)
{
	struct drm_display_info *info = &connector->display_info;

	u32 quirks = edid_get_quirks(edid);

	drm_reset_display_info(connector);

	info->width_mm = edid->width_cm * 10;
	info->height_mm = edid->height_cm * 10;

	info->non_desktop = !!(quirks & EDID_QUIRK_NON_DESKTOP);

	DRM_DEBUG_KMS("non_desktop set to %d\n", info->non_desktop);

	if (edid->revision < 3)
		return quirks;

	if (!(edid->input & DRM_EDID_INPUT_DIGITAL))
		return quirks;

	drm_parse_cea_ext(connector, edid);

	/*
	 * Digital sink with "DFP 1.x compliant TMDS" according to EDID 1.3?
	 *
	 * For such displays, the DFP spec 1.0, section 3.10 "EDID support"
	 * tells us to assume 8 bpc color depth if the EDID doesn't have
	 * extensions which tell otherwise.
	 */
	if (info->bpc == 0 && edid->revision == 3 &&
	    edid->input & DRM_EDID_DIGITAL_DFP_1_X) {
		info->bpc = 8;
		DRM_DEBUG("%s: Assigning DFP sink color depth as %d bpc.\n",
			  connector->name, info->bpc);
	}

	/* Only defined for 1.4 with digital displays */
	if (edid->revision < 4)
		return quirks;

	switch (edid->input & DRM_EDID_DIGITAL_DEPTH_MASK) {
	case DRM_EDID_DIGITAL_DEPTH_6:
		info->bpc = 6;
		break;
	case DRM_EDID_DIGITAL_DEPTH_8:
		info->bpc = 8;
		break;
	case DRM_EDID_DIGITAL_DEPTH_10:
		info->bpc = 10;
		break;
	case DRM_EDID_DIGITAL_DEPTH_12:
		info->bpc = 12;
		break;
	case DRM_EDID_DIGITAL_DEPTH_14:
		info->bpc = 14;
		break;
	case DRM_EDID_DIGITAL_DEPTH_16:
		info->bpc = 16;
		break;
	case DRM_EDID_DIGITAL_DEPTH_UNDEF:
	default:
		info->bpc = 0;
		break;
	}

	DRM_DEBUG("%s: Assigning EDID-1.4 digital sink color depth as %d bpc.\n",
			  connector->name, info->bpc);

	info->color_formats |= DRM_COLOR_FORMAT_RGB444;
	if (edid->features & DRM_EDID_FEATURE_RGB_YCRCB444)
		info->color_formats |= DRM_COLOR_FORMAT_YCRCB444;
	if (edid->features & DRM_EDID_FEATURE_RGB_YCRCB422)
		info->color_formats |= DRM_COLOR_FORMAT_YCRCB422;
	return quirks;
}