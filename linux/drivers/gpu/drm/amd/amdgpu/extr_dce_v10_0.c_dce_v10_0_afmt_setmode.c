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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct hdmi_avi_infoframe {int dummy; } ;
struct drm_encoder {scalar_t__ crtc; struct drm_device* dev; } ;
struct drm_display_mode {int /*<<< orphan*/  clock; } ;
struct drm_device {struct amdgpu_device* dev_private; } ;
struct drm_connector {int /*<<< orphan*/  name; } ;
struct amdgpu_encoder_atom_dig {TYPE_1__* afmt; } ;
struct amdgpu_encoder {struct amdgpu_encoder_atom_dig* enc_priv; } ;
struct amdgpu_device {int dummy; } ;
struct amdgpu_crtc {int bpc; } ;
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  buffer ;
struct TYPE_2__ {int /*<<< orphan*/  pin; scalar_t__ offset; int /*<<< orphan*/  enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  AFMT_60958_0 ; 
 int /*<<< orphan*/  AFMT_60958_1 ; 
 int /*<<< orphan*/  AFMT_60958_2 ; 
 int /*<<< orphan*/  AFMT_60958_CS_CHANNEL_NUMBER_2 ; 
 int /*<<< orphan*/  AFMT_60958_CS_CHANNEL_NUMBER_3 ; 
 int /*<<< orphan*/  AFMT_60958_CS_CHANNEL_NUMBER_4 ; 
 int /*<<< orphan*/  AFMT_60958_CS_CHANNEL_NUMBER_5 ; 
 int /*<<< orphan*/  AFMT_60958_CS_CHANNEL_NUMBER_6 ; 
 int /*<<< orphan*/  AFMT_60958_CS_CHANNEL_NUMBER_7 ; 
 int /*<<< orphan*/  AFMT_60958_CS_CHANNEL_NUMBER_L ; 
 int /*<<< orphan*/  AFMT_60958_CS_CHANNEL_NUMBER_R ; 
 int /*<<< orphan*/  AFMT_60958_CS_UPDATE ; 
 int /*<<< orphan*/  AFMT_AUDIO_INFO_UPDATE ; 
 int /*<<< orphan*/  AFMT_AUDIO_PACKET_CONTROL ; 
 int AFMT_AUDIO_PACKET_CONTROL2__AFMT_AUDIO_CHANNEL_ENABLE__SHIFT ; 
 int /*<<< orphan*/  AFMT_AUDIO_SAMPLE_SEND ; 
 int /*<<< orphan*/  AFMT_INFOFRAME_CONTROL0 ; 
 int /*<<< orphan*/  DRM_DEBUG (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,scalar_t__) ; 
 int /*<<< orphan*/  HDMI_ACR_AUTO_SEND ; 
 int /*<<< orphan*/  HDMI_ACR_PACKET_CONTROL ; 
 int /*<<< orphan*/  HDMI_ACR_SOURCE ; 
 int /*<<< orphan*/  HDMI_AUDIO_DELAY_EN ; 
 int /*<<< orphan*/  HDMI_AUDIO_INFO_CONT ; 
 int /*<<< orphan*/  HDMI_AUDIO_INFO_LINE ; 
 int /*<<< orphan*/  HDMI_AUDIO_INFO_SEND ; 
 int /*<<< orphan*/  HDMI_AUDIO_PACKETS_PER_LINE ; 
 int /*<<< orphan*/  HDMI_AUDIO_PACKET_CONTROL ; 
 int HDMI_AVI_INFOFRAME_SIZE ; 
 int /*<<< orphan*/  HDMI_AVI_INFO_CONT ; 
 int /*<<< orphan*/  HDMI_AVI_INFO_LINE ; 
 int /*<<< orphan*/  HDMI_AVI_INFO_SEND ; 
 int /*<<< orphan*/  HDMI_CONTROL ; 
 int /*<<< orphan*/  HDMI_DEEP_COLOR_DEPTH ; 
 int /*<<< orphan*/  HDMI_DEEP_COLOR_ENABLE ; 
 int /*<<< orphan*/  HDMI_GC_CONT ; 
 int /*<<< orphan*/  HDMI_GC_SEND ; 
 int /*<<< orphan*/  HDMI_INFOFRAME_CONTROL0 ; 
 int /*<<< orphan*/  HDMI_INFOFRAME_CONTROL1 ; 
 int HDMI_INFOFRAME_HEADER_SIZE ; 
 int /*<<< orphan*/  HDMI_NULL_SEND ; 
 int /*<<< orphan*/  HDMI_VBI_PACKET_CONTROL ; 
 int REG_SET_FIELD (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int RREG32 (scalar_t__) ; 
 int /*<<< orphan*/  WREG32 (scalar_t__,int) ; 
 struct drm_connector* amdgpu_get_connector_for_encoder (struct drm_encoder*) ; 
 int /*<<< orphan*/  dce_v10_0_afmt_audio_select_pin (struct drm_encoder*) ; 
 int /*<<< orphan*/  dce_v10_0_afmt_update_ACR (struct drm_encoder*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dce_v10_0_afmt_update_avi_infoframe (struct drm_encoder*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dce_v10_0_audio_enable (struct amdgpu_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dce_v10_0_audio_get_pin (struct amdgpu_device*) ; 
 int /*<<< orphan*/  dce_v10_0_audio_set_dto (struct drm_encoder*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dce_v10_0_audio_write_latency_fields (struct drm_encoder*,struct drm_display_mode*) ; 
 int /*<<< orphan*/  dce_v10_0_audio_write_sad_regs (struct drm_encoder*) ; 
 int /*<<< orphan*/  dce_v10_0_audio_write_speaker_allocation (struct drm_encoder*) ; 
 scalar_t__ drm_hdmi_avi_infoframe_from_display_mode (struct hdmi_avi_infoframe*,struct drm_connector*,struct drm_display_mode*) ; 
 scalar_t__ hdmi_avi_infoframe_pack (struct hdmi_avi_infoframe*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ mmAFMT_60958_0 ; 
 scalar_t__ mmAFMT_60958_1 ; 
 scalar_t__ mmAFMT_60958_2 ; 
 scalar_t__ mmAFMT_AUDIO_CRC_CONTROL ; 
 scalar_t__ mmAFMT_AUDIO_PACKET_CONTROL ; 
 scalar_t__ mmAFMT_AUDIO_PACKET_CONTROL2 ; 
 scalar_t__ mmAFMT_INFOFRAME_CONTROL0 ; 
 scalar_t__ mmAFMT_RAMP_CONTROL0 ; 
 scalar_t__ mmAFMT_RAMP_CONTROL1 ; 
 scalar_t__ mmAFMT_RAMP_CONTROL2 ; 
 scalar_t__ mmAFMT_RAMP_CONTROL3 ; 
 scalar_t__ mmHDMI_ACR_PACKET_CONTROL ; 
 scalar_t__ mmHDMI_AUDIO_PACKET_CONTROL ; 
 scalar_t__ mmHDMI_CONTROL ; 
 scalar_t__ mmHDMI_GC ; 
 scalar_t__ mmHDMI_INFOFRAME_CONTROL0 ; 
 scalar_t__ mmHDMI_INFOFRAME_CONTROL1 ; 
 scalar_t__ mmHDMI_VBI_PACKET_CONTROL ; 
 struct amdgpu_crtc* to_amdgpu_crtc (scalar_t__) ; 
 struct amdgpu_encoder* to_amdgpu_encoder (struct drm_encoder*) ; 

__attribute__((used)) static void dce_v10_0_afmt_setmode(struct drm_encoder *encoder,
				  struct drm_display_mode *mode)
{
	struct drm_device *dev = encoder->dev;
	struct amdgpu_device *adev = dev->dev_private;
	struct amdgpu_encoder *amdgpu_encoder = to_amdgpu_encoder(encoder);
	struct amdgpu_encoder_atom_dig *dig = amdgpu_encoder->enc_priv;
	struct drm_connector *connector = amdgpu_get_connector_for_encoder(encoder);
	u8 buffer[HDMI_INFOFRAME_HEADER_SIZE + HDMI_AVI_INFOFRAME_SIZE];
	struct hdmi_avi_infoframe frame;
	ssize_t err;
	u32 tmp;
	int bpc = 8;

	if (!dig || !dig->afmt)
		return;

	/* Silent, r600_hdmi_enable will raise WARN for us */
	if (!dig->afmt->enabled)
		return;

	/* hdmi deep color mode general control packets setup, if bpc > 8 */
	if (encoder->crtc) {
		struct amdgpu_crtc *amdgpu_crtc = to_amdgpu_crtc(encoder->crtc);
		bpc = amdgpu_crtc->bpc;
	}

	/* disable audio prior to setting up hw */
	dig->afmt->pin = dce_v10_0_audio_get_pin(adev);
	dce_v10_0_audio_enable(adev, dig->afmt->pin, false);

	dce_v10_0_audio_set_dto(encoder, mode->clock);

	tmp = RREG32(mmHDMI_VBI_PACKET_CONTROL + dig->afmt->offset);
	tmp = REG_SET_FIELD(tmp, HDMI_VBI_PACKET_CONTROL, HDMI_NULL_SEND, 1);
	WREG32(mmHDMI_VBI_PACKET_CONTROL + dig->afmt->offset, tmp); /* send null packets when required */

	WREG32(mmAFMT_AUDIO_CRC_CONTROL + dig->afmt->offset, 0x1000);

	tmp = RREG32(mmHDMI_CONTROL + dig->afmt->offset);
	switch (bpc) {
	case 0:
	case 6:
	case 8:
	case 16:
	default:
		tmp = REG_SET_FIELD(tmp, HDMI_CONTROL, HDMI_DEEP_COLOR_ENABLE, 0);
		tmp = REG_SET_FIELD(tmp, HDMI_CONTROL, HDMI_DEEP_COLOR_DEPTH, 0);
		DRM_DEBUG("%s: Disabling hdmi deep color for %d bpc.\n",
			  connector->name, bpc);
		break;
	case 10:
		tmp = REG_SET_FIELD(tmp, HDMI_CONTROL, HDMI_DEEP_COLOR_ENABLE, 1);
		tmp = REG_SET_FIELD(tmp, HDMI_CONTROL, HDMI_DEEP_COLOR_DEPTH, 1);
		DRM_DEBUG("%s: Enabling hdmi deep color 30 for 10 bpc.\n",
			  connector->name);
		break;
	case 12:
		tmp = REG_SET_FIELD(tmp, HDMI_CONTROL, HDMI_DEEP_COLOR_ENABLE, 1);
		tmp = REG_SET_FIELD(tmp, HDMI_CONTROL, HDMI_DEEP_COLOR_DEPTH, 2);
		DRM_DEBUG("%s: Enabling hdmi deep color 36 for 12 bpc.\n",
			  connector->name);
		break;
	}
	WREG32(mmHDMI_CONTROL + dig->afmt->offset, tmp);

	tmp = RREG32(mmHDMI_VBI_PACKET_CONTROL + dig->afmt->offset);
	tmp = REG_SET_FIELD(tmp, HDMI_VBI_PACKET_CONTROL, HDMI_NULL_SEND, 1); /* send null packets when required */
	tmp = REG_SET_FIELD(tmp, HDMI_VBI_PACKET_CONTROL, HDMI_GC_SEND, 1); /* send general control packets */
	tmp = REG_SET_FIELD(tmp, HDMI_VBI_PACKET_CONTROL, HDMI_GC_CONT, 1); /* send general control packets every frame */
	WREG32(mmHDMI_VBI_PACKET_CONTROL + dig->afmt->offset, tmp);

	tmp = RREG32(mmHDMI_INFOFRAME_CONTROL0 + dig->afmt->offset);
	/* enable audio info frames (frames won't be set until audio is enabled) */
	tmp = REG_SET_FIELD(tmp, HDMI_INFOFRAME_CONTROL0, HDMI_AUDIO_INFO_SEND, 1);
	/* required for audio info values to be updated */
	tmp = REG_SET_FIELD(tmp, HDMI_INFOFRAME_CONTROL0, HDMI_AUDIO_INFO_CONT, 1);
	WREG32(mmHDMI_INFOFRAME_CONTROL0 + dig->afmt->offset, tmp);

	tmp = RREG32(mmAFMT_INFOFRAME_CONTROL0 + dig->afmt->offset);
	/* required for audio info values to be updated */
	tmp = REG_SET_FIELD(tmp, AFMT_INFOFRAME_CONTROL0, AFMT_AUDIO_INFO_UPDATE, 1);
	WREG32(mmAFMT_INFOFRAME_CONTROL0 + dig->afmt->offset, tmp);

	tmp = RREG32(mmHDMI_INFOFRAME_CONTROL1 + dig->afmt->offset);
	/* anything other than 0 */
	tmp = REG_SET_FIELD(tmp, HDMI_INFOFRAME_CONTROL1, HDMI_AUDIO_INFO_LINE, 2);
	WREG32(mmHDMI_INFOFRAME_CONTROL1 + dig->afmt->offset, tmp);

	WREG32(mmHDMI_GC + dig->afmt->offset, 0); /* unset HDMI_GC_AVMUTE */

	tmp = RREG32(mmHDMI_AUDIO_PACKET_CONTROL + dig->afmt->offset);
	/* set the default audio delay */
	tmp = REG_SET_FIELD(tmp, HDMI_AUDIO_PACKET_CONTROL, HDMI_AUDIO_DELAY_EN, 1);
	/* should be suffient for all audio modes and small enough for all hblanks */
	tmp = REG_SET_FIELD(tmp, HDMI_AUDIO_PACKET_CONTROL, HDMI_AUDIO_PACKETS_PER_LINE, 3);
	WREG32(mmHDMI_AUDIO_PACKET_CONTROL + dig->afmt->offset, tmp);

	tmp = RREG32(mmAFMT_AUDIO_PACKET_CONTROL + dig->afmt->offset);
	/* allow 60958 channel status fields to be updated */
	tmp = REG_SET_FIELD(tmp, AFMT_AUDIO_PACKET_CONTROL, AFMT_60958_CS_UPDATE, 1);
	WREG32(mmAFMT_AUDIO_PACKET_CONTROL + dig->afmt->offset, tmp);

	tmp = RREG32(mmHDMI_ACR_PACKET_CONTROL + dig->afmt->offset);
	if (bpc > 8)
		/* clear SW CTS value */
		tmp = REG_SET_FIELD(tmp, HDMI_ACR_PACKET_CONTROL, HDMI_ACR_SOURCE, 0);
	else
		/* select SW CTS value */
		tmp = REG_SET_FIELD(tmp, HDMI_ACR_PACKET_CONTROL, HDMI_ACR_SOURCE, 1);
	/* allow hw to sent ACR packets when required */
	tmp = REG_SET_FIELD(tmp, HDMI_ACR_PACKET_CONTROL, HDMI_ACR_AUTO_SEND, 1);
	WREG32(mmHDMI_ACR_PACKET_CONTROL + dig->afmt->offset, tmp);

	dce_v10_0_afmt_update_ACR(encoder, mode->clock);

	tmp = RREG32(mmAFMT_60958_0 + dig->afmt->offset);
	tmp = REG_SET_FIELD(tmp, AFMT_60958_0, AFMT_60958_CS_CHANNEL_NUMBER_L, 1);
	WREG32(mmAFMT_60958_0 + dig->afmt->offset, tmp);

	tmp = RREG32(mmAFMT_60958_1 + dig->afmt->offset);
	tmp = REG_SET_FIELD(tmp, AFMT_60958_1, AFMT_60958_CS_CHANNEL_NUMBER_R, 2);
	WREG32(mmAFMT_60958_1 + dig->afmt->offset, tmp);

	tmp = RREG32(mmAFMT_60958_2 + dig->afmt->offset);
	tmp = REG_SET_FIELD(tmp, AFMT_60958_2, AFMT_60958_CS_CHANNEL_NUMBER_2, 3);
	tmp = REG_SET_FIELD(tmp, AFMT_60958_2, AFMT_60958_CS_CHANNEL_NUMBER_3, 4);
	tmp = REG_SET_FIELD(tmp, AFMT_60958_2, AFMT_60958_CS_CHANNEL_NUMBER_4, 5);
	tmp = REG_SET_FIELD(tmp, AFMT_60958_2, AFMT_60958_CS_CHANNEL_NUMBER_5, 6);
	tmp = REG_SET_FIELD(tmp, AFMT_60958_2, AFMT_60958_CS_CHANNEL_NUMBER_6, 7);
	tmp = REG_SET_FIELD(tmp, AFMT_60958_2, AFMT_60958_CS_CHANNEL_NUMBER_7, 8);
	WREG32(mmAFMT_60958_2 + dig->afmt->offset, tmp);

	dce_v10_0_audio_write_speaker_allocation(encoder);

	WREG32(mmAFMT_AUDIO_PACKET_CONTROL2 + dig->afmt->offset,
	       (0xff << AFMT_AUDIO_PACKET_CONTROL2__AFMT_AUDIO_CHANNEL_ENABLE__SHIFT));

	dce_v10_0_afmt_audio_select_pin(encoder);
	dce_v10_0_audio_write_sad_regs(encoder);
	dce_v10_0_audio_write_latency_fields(encoder, mode);

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

	dce_v10_0_afmt_update_avi_infoframe(encoder, buffer, sizeof(buffer));

	tmp = RREG32(mmHDMI_INFOFRAME_CONTROL0 + dig->afmt->offset);
	/* enable AVI info frames */
	tmp = REG_SET_FIELD(tmp, HDMI_INFOFRAME_CONTROL0, HDMI_AVI_INFO_SEND, 1);
	/* required for audio info values to be updated */
	tmp = REG_SET_FIELD(tmp, HDMI_INFOFRAME_CONTROL0, HDMI_AVI_INFO_CONT, 1);
	WREG32(mmHDMI_INFOFRAME_CONTROL0 + dig->afmt->offset, tmp);

	tmp = RREG32(mmHDMI_INFOFRAME_CONTROL1 + dig->afmt->offset);
	tmp = REG_SET_FIELD(tmp, HDMI_INFOFRAME_CONTROL1, HDMI_AVI_INFO_LINE, 2);
	WREG32(mmHDMI_INFOFRAME_CONTROL1 + dig->afmt->offset, tmp);

	tmp = RREG32(mmAFMT_AUDIO_PACKET_CONTROL + dig->afmt->offset);
	/* send audio packets */
	tmp = REG_SET_FIELD(tmp, AFMT_AUDIO_PACKET_CONTROL, AFMT_AUDIO_SAMPLE_SEND, 1);
	WREG32(mmAFMT_AUDIO_PACKET_CONTROL + dig->afmt->offset, tmp);

	WREG32(mmAFMT_RAMP_CONTROL0 + dig->afmt->offset, 0x00FFFFFF);
	WREG32(mmAFMT_RAMP_CONTROL1 + dig->afmt->offset, 0x007FFFFF);
	WREG32(mmAFMT_RAMP_CONTROL2 + dig->afmt->offset, 0x00000001);
	WREG32(mmAFMT_RAMP_CONTROL3 + dig->afmt->offset, 0x00000001);

	/* enable audio after to setting up hw */
	dce_v10_0_audio_enable(adev, dig->afmt->pin, true);
}