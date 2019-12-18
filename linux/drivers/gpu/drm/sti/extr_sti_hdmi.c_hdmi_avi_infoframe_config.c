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
typedef  int /*<<< orphan*/  u8 ;
struct drm_display_mode {int dummy; } ;
struct sti_hdmi {int /*<<< orphan*/  colorspace; int /*<<< orphan*/  drm_connector; struct drm_display_mode mode; } ;
struct hdmi_avi_infoframe {int /*<<< orphan*/  colorimetry; int /*<<< orphan*/  quantization_range; int /*<<< orphan*/  colorspace; } ;
typedef  int /*<<< orphan*/  buffer ;

/* Variables and functions */
 int /*<<< orphan*/  AVI ; 
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int /*<<< orphan*/  HDMI_COLORIMETRY_NONE ; 
 int HDMI_INFOFRAME_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HDMI_QUANTIZATION_RANGE_DEFAULT ; 
 int drm_hdmi_avi_infoframe_from_display_mode (struct hdmi_avi_infoframe*,int /*<<< orphan*/ ,struct drm_display_mode*) ; 
 int hdmi_avi_infoframe_pack (struct hdmi_avi_infoframe*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  hdmi_infoframe_write_infopack (struct sti_hdmi*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int hdmi_avi_infoframe_config(struct sti_hdmi *hdmi)
{
	struct drm_display_mode *mode = &hdmi->mode;
	struct hdmi_avi_infoframe infoframe;
	u8 buffer[HDMI_INFOFRAME_SIZE(AVI)];
	int ret;

	DRM_DEBUG_DRIVER("\n");

	ret = drm_hdmi_avi_infoframe_from_display_mode(&infoframe,
						       hdmi->drm_connector, mode);
	if (ret < 0) {
		DRM_ERROR("failed to setup AVI infoframe: %d\n", ret);
		return ret;
	}

	/* fixed infoframe configuration not linked to the mode */
	infoframe.colorspace = hdmi->colorspace;
	infoframe.quantization_range = HDMI_QUANTIZATION_RANGE_DEFAULT;
	infoframe.colorimetry = HDMI_COLORIMETRY_NONE;

	ret = hdmi_avi_infoframe_pack(&infoframe, buffer, sizeof(buffer));
	if (ret < 0) {
		DRM_ERROR("failed to pack AVI infoframe: %d\n", ret);
		return ret;
	}

	hdmi_infoframe_write_infopack(hdmi, buffer, ret);

	return 0;
}