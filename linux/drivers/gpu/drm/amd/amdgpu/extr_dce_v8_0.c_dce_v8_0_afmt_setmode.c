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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  u8 ;
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
struct TYPE_2__ {int offset; int /*<<< orphan*/  pin; int /*<<< orphan*/  enabled; } ;

/* Variables and functions */
 int AFMT_60958_0__AFMT_60958_CS_CHANNEL_NUMBER_L__SHIFT ; 
 int AFMT_60958_1__AFMT_60958_CS_CHANNEL_NUMBER_R__SHIFT ; 
 int AFMT_60958_2__AFMT_60958_CS_CHANNEL_NUMBER_2__SHIFT ; 
 int AFMT_60958_2__AFMT_60958_CS_CHANNEL_NUMBER_3__SHIFT ; 
 int AFMT_60958_2__AFMT_60958_CS_CHANNEL_NUMBER_4__SHIFT ; 
 int AFMT_60958_2__AFMT_60958_CS_CHANNEL_NUMBER_5__SHIFT ; 
 int AFMT_60958_2__AFMT_60958_CS_CHANNEL_NUMBER_6__SHIFT ; 
 int AFMT_60958_2__AFMT_60958_CS_CHANNEL_NUMBER_7__SHIFT ; 
 int AFMT_AUDIO_PACKET_CONTROL2__AFMT_AUDIO_CHANNEL_ENABLE__SHIFT ; 
 int AFMT_AUDIO_PACKET_CONTROL__AFMT_60958_CS_UPDATE_MASK ; 
 int AFMT_AUDIO_PACKET_CONTROL__AFMT_AUDIO_SAMPLE_SEND_MASK ; 
 int AFMT_INFOFRAME_CONTROL0__AFMT_AUDIO_INFO_UPDATE_MASK ; 
 int /*<<< orphan*/  DRM_DEBUG (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,scalar_t__) ; 
 int HDMI_ACR_PACKET_CONTROL__HDMI_ACR_AUTO_SEND_MASK ; 
 int HDMI_ACR_PACKET_CONTROL__HDMI_ACR_SOURCE_MASK ; 
 int HDMI_AUDIO_PACKET_CONTROL__HDMI_AUDIO_DELAY_EN__SHIFT ; 
 int HDMI_AUDIO_PACKET_CONTROL__HDMI_AUDIO_PACKETS_PER_LINE__SHIFT ; 
 int HDMI_AVI_INFOFRAME_SIZE ; 
 int HDMI_CONTROL__HDMI_DEEP_COLOR_DEPTH_MASK ; 
 int HDMI_CONTROL__HDMI_DEEP_COLOR_DEPTH__SHIFT ; 
 int HDMI_CONTROL__HDMI_DEEP_COLOR_ENABLE_MASK ; 
 int HDMI_INFOFRAME_CONTROL0__HDMI_AUDIO_INFO_CONT_MASK ; 
 int HDMI_INFOFRAME_CONTROL0__HDMI_AUDIO_INFO_SEND_MASK ; 
 int HDMI_INFOFRAME_CONTROL0__HDMI_AVI_INFO_CONT_MASK ; 
 int HDMI_INFOFRAME_CONTROL0__HDMI_AVI_INFO_SEND_MASK ; 
 int HDMI_INFOFRAME_CONTROL1__HDMI_AUDIO_INFO_LINE__SHIFT ; 
 int /*<<< orphan*/  HDMI_INFOFRAME_CONTROL1__HDMI_AVI_INFO_LINE_MASK ; 
 int HDMI_INFOFRAME_CONTROL1__HDMI_AVI_INFO_LINE__SHIFT ; 
 int HDMI_INFOFRAME_HEADER_SIZE ; 
 int HDMI_VBI_PACKET_CONTROL__HDMI_GC_CONT_MASK ; 
 int HDMI_VBI_PACKET_CONTROL__HDMI_GC_SEND_MASK ; 
 int HDMI_VBI_PACKET_CONTROL__HDMI_NULL_SEND_MASK ; 
 int RREG32 (int) ; 
 int /*<<< orphan*/  WREG32 (int,int) ; 
 int /*<<< orphan*/  WREG32_OR (int,int) ; 
 int /*<<< orphan*/  WREG32_P (int,int,int /*<<< orphan*/ ) ; 
 struct drm_connector* amdgpu_get_connector_for_encoder (struct drm_encoder*) ; 
 int /*<<< orphan*/  dce_v8_0_afmt_audio_select_pin (struct drm_encoder*) ; 
 int /*<<< orphan*/  dce_v8_0_afmt_update_ACR (struct drm_encoder*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dce_v8_0_afmt_update_avi_infoframe (struct drm_encoder*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dce_v8_0_audio_enable (struct amdgpu_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dce_v8_0_audio_get_pin (struct amdgpu_device*) ; 
 int /*<<< orphan*/  dce_v8_0_audio_set_dto (struct drm_encoder*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dce_v8_0_audio_write_latency_fields (struct drm_encoder*,struct drm_display_mode*) ; 
 int /*<<< orphan*/  dce_v8_0_audio_write_sad_regs (struct drm_encoder*) ; 
 int /*<<< orphan*/  dce_v8_0_audio_write_speaker_allocation (struct drm_encoder*) ; 
 scalar_t__ drm_hdmi_avi_infoframe_from_display_mode (struct hdmi_avi_infoframe*,struct drm_connector*,struct drm_display_mode*) ; 
 scalar_t__ hdmi_avi_infoframe_pack (struct hdmi_avi_infoframe*,int /*<<< orphan*/ *,int) ; 
 int mmAFMT_60958_0 ; 
 int mmAFMT_60958_1 ; 
 int mmAFMT_60958_2 ; 
 int mmAFMT_AUDIO_CRC_CONTROL ; 
 int mmAFMT_AUDIO_PACKET_CONTROL ; 
 int mmAFMT_AUDIO_PACKET_CONTROL2 ; 
 int mmAFMT_INFOFRAME_CONTROL0 ; 
 int mmAFMT_RAMP_CONTROL0 ; 
 int mmAFMT_RAMP_CONTROL1 ; 
 int mmAFMT_RAMP_CONTROL2 ; 
 int mmAFMT_RAMP_CONTROL3 ; 
 int mmHDMI_ACR_PACKET_CONTROL ; 
 int mmHDMI_AUDIO_PACKET_CONTROL ; 
 int mmHDMI_CONTROL ; 
 int mmHDMI_GC ; 
 int mmHDMI_INFOFRAME_CONTROL0 ; 
 int mmHDMI_INFOFRAME_CONTROL1 ; 
 int mmHDMI_VBI_PACKET_CONTROL ; 
 struct amdgpu_crtc* to_amdgpu_crtc (scalar_t__) ; 
 struct amdgpu_encoder* to_amdgpu_encoder (struct drm_encoder*) ; 

__attribute__((used)) static void dce_v8_0_afmt_setmode(struct drm_encoder *encoder,
				  struct drm_display_mode *mode)
{
	struct drm_device *dev = encoder->dev;
	struct amdgpu_device *adev = dev->dev_private;
	struct amdgpu_encoder *amdgpu_encoder = to_amdgpu_encoder(encoder);
	struct amdgpu_encoder_atom_dig *dig = amdgpu_encoder->enc_priv;
	struct drm_connector *connector = amdgpu_get_connector_for_encoder(encoder);
	u8 buffer[HDMI_INFOFRAME_HEADER_SIZE + HDMI_AVI_INFOFRAME_SIZE];
	struct hdmi_avi_infoframe frame;
	uint32_t offset, val;
	ssize_t err;
	int bpc = 8;

	if (!dig || !dig->afmt)
		return;

	/* Silent, r600_hdmi_enable will raise WARN for us */
	if (!dig->afmt->enabled)
		return;

	offset = dig->afmt->offset;

	/* hdmi deep color mode general control packets setup, if bpc > 8 */
	if (encoder->crtc) {
		struct amdgpu_crtc *amdgpu_crtc = to_amdgpu_crtc(encoder->crtc);
		bpc = amdgpu_crtc->bpc;
	}

	/* disable audio prior to setting up hw */
	dig->afmt->pin = dce_v8_0_audio_get_pin(adev);
	dce_v8_0_audio_enable(adev, dig->afmt->pin, false);

	dce_v8_0_audio_set_dto(encoder, mode->clock);

	WREG32(mmHDMI_VBI_PACKET_CONTROL + offset,
	       HDMI_VBI_PACKET_CONTROL__HDMI_NULL_SEND_MASK); /* send null packets when required */

	WREG32(mmAFMT_AUDIO_CRC_CONTROL + offset, 0x1000);

	val = RREG32(mmHDMI_CONTROL + offset);
	val &= ~HDMI_CONTROL__HDMI_DEEP_COLOR_ENABLE_MASK;
	val &= ~HDMI_CONTROL__HDMI_DEEP_COLOR_DEPTH_MASK;

	switch (bpc) {
	case 0:
	case 6:
	case 8:
	case 16:
	default:
		DRM_DEBUG("%s: Disabling hdmi deep color for %d bpc.\n",
			  connector->name, bpc);
		break;
	case 10:
		val |= HDMI_CONTROL__HDMI_DEEP_COLOR_ENABLE_MASK;
		val |= 1 << HDMI_CONTROL__HDMI_DEEP_COLOR_DEPTH__SHIFT;
		DRM_DEBUG("%s: Enabling hdmi deep color 30 for 10 bpc.\n",
			  connector->name);
		break;
	case 12:
		val |= HDMI_CONTROL__HDMI_DEEP_COLOR_ENABLE_MASK;
		val |= 2 << HDMI_CONTROL__HDMI_DEEP_COLOR_DEPTH__SHIFT;
		DRM_DEBUG("%s: Enabling hdmi deep color 36 for 12 bpc.\n",
			  connector->name);
		break;
	}

	WREG32(mmHDMI_CONTROL + offset, val);

	WREG32(mmHDMI_VBI_PACKET_CONTROL + offset,
	       HDMI_VBI_PACKET_CONTROL__HDMI_NULL_SEND_MASK | /* send null packets when required */
	       HDMI_VBI_PACKET_CONTROL__HDMI_GC_SEND_MASK | /* send general control packets */
	       HDMI_VBI_PACKET_CONTROL__HDMI_GC_CONT_MASK); /* send general control packets every frame */

	WREG32(mmHDMI_INFOFRAME_CONTROL0 + offset,
	       HDMI_INFOFRAME_CONTROL0__HDMI_AUDIO_INFO_SEND_MASK | /* enable audio info frames (frames won't be set until audio is enabled) */
	       HDMI_INFOFRAME_CONTROL0__HDMI_AUDIO_INFO_CONT_MASK); /* required for audio info values to be updated */

	WREG32(mmAFMT_INFOFRAME_CONTROL0 + offset,
	       AFMT_INFOFRAME_CONTROL0__AFMT_AUDIO_INFO_UPDATE_MASK); /* required for audio info values to be updated */

	WREG32(mmHDMI_INFOFRAME_CONTROL1 + offset,
	       (2 << HDMI_INFOFRAME_CONTROL1__HDMI_AUDIO_INFO_LINE__SHIFT)); /* anything other than 0 */

	WREG32(mmHDMI_GC + offset, 0); /* unset HDMI_GC_AVMUTE */

	WREG32(mmHDMI_AUDIO_PACKET_CONTROL + offset,
	       (1 << HDMI_AUDIO_PACKET_CONTROL__HDMI_AUDIO_DELAY_EN__SHIFT) | /* set the default audio delay */
	       (3 << HDMI_AUDIO_PACKET_CONTROL__HDMI_AUDIO_PACKETS_PER_LINE__SHIFT)); /* should be suffient for all audio modes and small enough for all hblanks */

	WREG32(mmAFMT_AUDIO_PACKET_CONTROL + offset,
	       AFMT_AUDIO_PACKET_CONTROL__AFMT_60958_CS_UPDATE_MASK); /* allow 60958 channel status fields to be updated */

	/* fglrx clears sth in AFMT_AUDIO_PACKET_CONTROL2 here */

	if (bpc > 8)
		WREG32(mmHDMI_ACR_PACKET_CONTROL + offset,
		       HDMI_ACR_PACKET_CONTROL__HDMI_ACR_AUTO_SEND_MASK); /* allow hw to sent ACR packets when required */
	else
		WREG32(mmHDMI_ACR_PACKET_CONTROL + offset,
		       HDMI_ACR_PACKET_CONTROL__HDMI_ACR_SOURCE_MASK | /* select SW CTS value */
		       HDMI_ACR_PACKET_CONTROL__HDMI_ACR_AUTO_SEND_MASK); /* allow hw to sent ACR packets when required */

	dce_v8_0_afmt_update_ACR(encoder, mode->clock);

	WREG32(mmAFMT_60958_0 + offset,
	       (1 << AFMT_60958_0__AFMT_60958_CS_CHANNEL_NUMBER_L__SHIFT));

	WREG32(mmAFMT_60958_1 + offset,
	       (2 << AFMT_60958_1__AFMT_60958_CS_CHANNEL_NUMBER_R__SHIFT));

	WREG32(mmAFMT_60958_2 + offset,
	       (3 << AFMT_60958_2__AFMT_60958_CS_CHANNEL_NUMBER_2__SHIFT) |
	       (4 << AFMT_60958_2__AFMT_60958_CS_CHANNEL_NUMBER_3__SHIFT) |
	       (5 << AFMT_60958_2__AFMT_60958_CS_CHANNEL_NUMBER_4__SHIFT) |
	       (6 << AFMT_60958_2__AFMT_60958_CS_CHANNEL_NUMBER_5__SHIFT) |
	       (7 << AFMT_60958_2__AFMT_60958_CS_CHANNEL_NUMBER_6__SHIFT) |
	       (8 << AFMT_60958_2__AFMT_60958_CS_CHANNEL_NUMBER_7__SHIFT));

	dce_v8_0_audio_write_speaker_allocation(encoder);


	WREG32(mmAFMT_AUDIO_PACKET_CONTROL2 + offset,
	       (0xff << AFMT_AUDIO_PACKET_CONTROL2__AFMT_AUDIO_CHANNEL_ENABLE__SHIFT));

	dce_v8_0_afmt_audio_select_pin(encoder);
	dce_v8_0_audio_write_sad_regs(encoder);
	dce_v8_0_audio_write_latency_fields(encoder, mode);

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

	dce_v8_0_afmt_update_avi_infoframe(encoder, buffer, sizeof(buffer));

	WREG32_OR(mmHDMI_INFOFRAME_CONTROL0 + offset,
		  HDMI_INFOFRAME_CONTROL0__HDMI_AVI_INFO_SEND_MASK | /* enable AVI info frames */
		  HDMI_INFOFRAME_CONTROL0__HDMI_AVI_INFO_CONT_MASK); /* required for audio info values to be updated */

	WREG32_P(mmHDMI_INFOFRAME_CONTROL1 + offset,
		 (2 << HDMI_INFOFRAME_CONTROL1__HDMI_AVI_INFO_LINE__SHIFT), /* anything other than 0 */
		 ~HDMI_INFOFRAME_CONTROL1__HDMI_AVI_INFO_LINE_MASK);

	WREG32_OR(mmAFMT_AUDIO_PACKET_CONTROL + offset,
		  AFMT_AUDIO_PACKET_CONTROL__AFMT_AUDIO_SAMPLE_SEND_MASK); /* send audio packets */

	WREG32(mmAFMT_RAMP_CONTROL0 + offset, 0x00FFFFFF);
	WREG32(mmAFMT_RAMP_CONTROL1 + offset, 0x007FFFFF);
	WREG32(mmAFMT_RAMP_CONTROL2 + offset, 0x00000001);
	WREG32(mmAFMT_RAMP_CONTROL3 + offset, 0x00000001);

	/* enable audio after setting up hw */
	dce_v8_0_audio_enable(adev, dig->afmt->pin, true);
}