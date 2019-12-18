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
typedef  int uint8_t ;
typedef  int u8 ;
typedef  int u32 ;
struct hdmi_avi_infoframe {int dummy; } ;
struct drm_encoder {struct drm_device* dev; } ;
struct drm_display_mode {int dummy; } ;
struct drm_device {struct amdgpu_device* dev_private; } ;
struct drm_connector {int dummy; } ;
struct amdgpu_encoder_atom_dig {TYPE_1__* afmt; } ;
struct amdgpu_encoder {struct amdgpu_encoder_atom_dig* enc_priv; } ;
struct amdgpu_device {int dummy; } ;
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  buffer ;
struct TYPE_2__ {scalar_t__ offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,scalar_t__) ; 
 int /*<<< orphan*/  HDMI_AUDIO_INFO_LINE ; 
 int HDMI_AVI_INFOFRAME_SIZE ; 
 int /*<<< orphan*/  HDMI_INFOFRAME_CONTROL1 ; 
 int HDMI_INFOFRAME_HEADER_SIZE ; 
 int REG_SET_FIELD (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int RREG32 (scalar_t__) ; 
 int /*<<< orphan*/  WREG32 (scalar_t__,int) ; 
 struct drm_connector* amdgpu_get_connector_for_encoder (struct drm_encoder*) ; 
 scalar_t__ drm_hdmi_avi_infoframe_from_display_mode (struct hdmi_avi_infoframe*,struct drm_connector*,struct drm_display_mode*) ; 
 scalar_t__ hdmi_avi_infoframe_pack (struct hdmi_avi_infoframe*,int*,int) ; 
 scalar_t__ mmAFMT_AVI_INFO0 ; 
 scalar_t__ mmAFMT_AVI_INFO1 ; 
 scalar_t__ mmAFMT_AVI_INFO2 ; 
 scalar_t__ mmAFMT_AVI_INFO3 ; 
 scalar_t__ mmHDMI_INFOFRAME_CONTROL1 ; 
 struct amdgpu_encoder* to_amdgpu_encoder (struct drm_encoder*) ; 

__attribute__((used)) static void dce_v6_0_audio_set_avi_infoframe(struct drm_encoder *encoder,
					       struct drm_display_mode *mode)
{
	struct drm_device *dev = encoder->dev;
	struct amdgpu_device *adev = dev->dev_private;
	struct amdgpu_encoder *amdgpu_encoder = to_amdgpu_encoder(encoder);
	struct amdgpu_encoder_atom_dig *dig = amdgpu_encoder->enc_priv;
	struct drm_connector *connector = amdgpu_get_connector_for_encoder(encoder);
	struct hdmi_avi_infoframe frame;
	u8 buffer[HDMI_INFOFRAME_HEADER_SIZE + HDMI_AVI_INFOFRAME_SIZE];
	uint8_t *payload = buffer + 3;
	uint8_t *header = buffer;
	ssize_t err;
	u32 tmp;

	err = drm_hdmi_avi_infoframe_from_display_mode(&frame, connector, mode);
	if (err < 0) {
		DRM_ERROR("failed to setup AVI infoframe: %zd\n", err);
		return;
	}

	err = hdmi_avi_infoframe_pack(&frame, buffer, sizeof(buffer));
	if (err < 0) {
		DRM_ERROR("failed to pack AVI infoframe: %zd\n", err);
		return;
	}

	WREG32(mmAFMT_AVI_INFO0 + dig->afmt->offset,
	       payload[0x0] | (payload[0x1] << 8) | (payload[0x2] << 16) | (payload[0x3] << 24));
	WREG32(mmAFMT_AVI_INFO1 + dig->afmt->offset,
	       payload[0x4] | (payload[0x5] << 8) | (payload[0x6] << 16) | (payload[0x7] << 24));
	WREG32(mmAFMT_AVI_INFO2 + dig->afmt->offset,
	       payload[0x8] | (payload[0x9] << 8) | (payload[0xA] << 16) | (payload[0xB] << 24));
	WREG32(mmAFMT_AVI_INFO3 + dig->afmt->offset,
	       payload[0xC] | (payload[0xD] << 8) | (header[1] << 24));

	tmp = RREG32(mmHDMI_INFOFRAME_CONTROL1 + dig->afmt->offset);
	/* anything other than 0 */
	tmp = REG_SET_FIELD(tmp, HDMI_INFOFRAME_CONTROL1,
			HDMI_AUDIO_INFO_LINE, 2);
	WREG32(mmHDMI_INFOFRAME_CONTROL1 + dig->afmt->offset, tmp);
}