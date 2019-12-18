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
typedef  int /*<<< orphan*/  u8 ;
struct radeon_encoder_atom_dig {TYPE_3__* afmt; } ;
struct radeon_encoder {scalar_t__ output_csc; TYPE_2__* audio; struct radeon_encoder_atom_dig* enc_priv; } ;
struct radeon_device {int dummy; } ;
struct hdmi_avi_infoframe {int dummy; } ;
struct drm_encoder {TYPE_1__* dev; } ;
struct drm_display_mode {int dummy; } ;
struct drm_connector {int dummy; } ;
typedef  int /*<<< orphan*/  buffer ;
struct TYPE_6__ {int /*<<< orphan*/  offset; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* set_avi_packet ) (struct radeon_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ;} ;
struct TYPE_4__ {struct radeon_device* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int EINVAL ; 
 int HDMI_AVI_INFOFRAME_SIZE ; 
 int HDMI_INFOFRAME_HEADER_SIZE ; 
 int /*<<< orphan*/  HDMI_QUANTIZATION_RANGE_FULL ; 
 int /*<<< orphan*/  HDMI_QUANTIZATION_RANGE_LIMITED ; 
 scalar_t__ RADEON_OUTPUT_CSC_BYPASS ; 
 scalar_t__ RADEON_OUTPUT_CSC_TVRGB ; 
 int drm_hdmi_avi_infoframe_from_display_mode (struct hdmi_avi_infoframe*,struct drm_connector*,struct drm_display_mode*) ; 
 int /*<<< orphan*/  drm_hdmi_avi_infoframe_quant_range (struct hdmi_avi_infoframe*,struct drm_connector*,struct drm_display_mode*,int /*<<< orphan*/ ) ; 
 int hdmi_avi_infoframe_pack (struct hdmi_avi_infoframe*,int /*<<< orphan*/ *,int) ; 
 struct drm_connector* radeon_get_connector_for_encoder (struct drm_encoder*) ; 
 int /*<<< orphan*/  stub1 (struct radeon_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 struct radeon_encoder* to_radeon_encoder (struct drm_encoder*) ; 

__attribute__((used)) static int radeon_audio_set_avi_packet(struct drm_encoder *encoder,
				       struct drm_display_mode *mode)
{
	struct radeon_device *rdev = encoder->dev->dev_private;
	struct radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
	struct radeon_encoder_atom_dig *dig = radeon_encoder->enc_priv;
	struct drm_connector *connector = radeon_get_connector_for_encoder(encoder);
	u8 buffer[HDMI_INFOFRAME_HEADER_SIZE + HDMI_AVI_INFOFRAME_SIZE];
	struct hdmi_avi_infoframe frame;
	int err;

	if (!connector)
		return -EINVAL;

	err = drm_hdmi_avi_infoframe_from_display_mode(&frame, connector, mode);
	if (err < 0) {
		DRM_ERROR("failed to setup AVI infoframe: %d\n", err);
		return err;
	}

	if (radeon_encoder->output_csc != RADEON_OUTPUT_CSC_BYPASS) {
		drm_hdmi_avi_infoframe_quant_range(&frame, connector, mode,
						   radeon_encoder->output_csc == RADEON_OUTPUT_CSC_TVRGB ?
						   HDMI_QUANTIZATION_RANGE_LIMITED :
						   HDMI_QUANTIZATION_RANGE_FULL);
	}

	err = hdmi_avi_infoframe_pack(&frame, buffer, sizeof(buffer));
	if (err < 0) {
		DRM_ERROR("failed to pack AVI infoframe: %d\n", err);
		return err;
	}

	if (dig && dig->afmt && radeon_encoder->audio &&
	    radeon_encoder->audio->set_avi_packet)
		radeon_encoder->audio->set_avi_packet(rdev, dig->afmt->offset,
			buffer, sizeof(buffer));

	return 0;
}