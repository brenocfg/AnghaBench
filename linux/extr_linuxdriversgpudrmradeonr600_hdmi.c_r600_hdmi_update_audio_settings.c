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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct radeon_encoder_atom_dig {TYPE_1__* afmt; } ;
struct radeon_encoder {struct radeon_encoder_atom_dig* enc_priv; } ;
struct radeon_device {int dummy; } ;
struct r600_audio_pin {int /*<<< orphan*/  channels; scalar_t__ category_code; scalar_t__ status_bits; int /*<<< orphan*/  bits_per_sample; int /*<<< orphan*/  rate; } ;
struct hdmi_audio_infoframe {int /*<<< orphan*/  channels; } ;
struct drm_encoder {struct drm_device* dev; } ;
struct drm_device {struct radeon_device* dev_private; } ;
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  buffer ;
struct TYPE_2__ {int offset; int /*<<< orphan*/  enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*,...) ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int HDMI0_AUDIO_INFO_CONT ; 
 int /*<<< orphan*/  HDMI0_AUDIO_INFO_SOURCE ; 
 int HDMI0_AUDIO_INFO_UPDATE ; 
 int HDMI0_AUDIO_PACKET_CONTROL ; 
 int HDMI0_AUDIO_TEST_EN ; 
 int HDMI0_CONTROL ; 
 int HDMI0_ERROR_ACK ; 
 int HDMI0_INFOFRAME_CONTROL0 ; 
 int HDMI_AUDIO_INFOFRAME_SIZE ; 
 int HDMI_INFOFRAME_HEADER_SIZE ; 
 int RREG32 (int) ; 
 int /*<<< orphan*/  WREG32 (int,int) ; 
 int /*<<< orphan*/  WREG32_AND (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32_OR (int,int) ; 
 scalar_t__ hdmi_audio_infoframe_init (struct hdmi_audio_infoframe*) ; 
 scalar_t__ hdmi_audio_infoframe_pack (struct hdmi_audio_infoframe*,int /*<<< orphan*/ *,int) ; 
 struct r600_audio_pin r600_audio_status (struct radeon_device*) ; 
 scalar_t__ r600_hdmi_is_audio_buffer_filled (struct drm_encoder*) ; 
 int /*<<< orphan*/  r600_hdmi_update_audio_infoframe (struct drm_encoder*,int /*<<< orphan*/ *,int) ; 
 struct radeon_encoder* to_radeon_encoder (struct drm_encoder*) ; 

void r600_hdmi_update_audio_settings(struct drm_encoder *encoder)
{
	struct drm_device *dev = encoder->dev;
	struct radeon_device *rdev = dev->dev_private;
	struct radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
	struct radeon_encoder_atom_dig *dig = radeon_encoder->enc_priv;
	struct r600_audio_pin audio = r600_audio_status(rdev);
	uint8_t buffer[HDMI_INFOFRAME_HEADER_SIZE + HDMI_AUDIO_INFOFRAME_SIZE];
	struct hdmi_audio_infoframe frame;
	uint32_t offset;
	uint32_t value;
	ssize_t err;

	if (!dig->afmt || !dig->afmt->enabled)
		return;
	offset = dig->afmt->offset;

	DRM_DEBUG("%s with %d channels, %d Hz sampling rate, %d bits per sample,\n",
		 r600_hdmi_is_audio_buffer_filled(encoder) ? "playing" : "stopped",
		  audio.channels, audio.rate, audio.bits_per_sample);
	DRM_DEBUG("0x%02X IEC60958 status bits and 0x%02X category code\n",
		  (int)audio.status_bits, (int)audio.category_code);

	err = hdmi_audio_infoframe_init(&frame);
	if (err < 0) {
		DRM_ERROR("failed to setup audio infoframe\n");
		return;
	}

	frame.channels = audio.channels;

	err = hdmi_audio_infoframe_pack(&frame, buffer, sizeof(buffer));
	if (err < 0) {
		DRM_ERROR("failed to pack audio infoframe\n");
		return;
	}

	value = RREG32(HDMI0_AUDIO_PACKET_CONTROL + offset);
	if (value & HDMI0_AUDIO_TEST_EN)
		WREG32(HDMI0_AUDIO_PACKET_CONTROL + offset,
		       value & ~HDMI0_AUDIO_TEST_EN);

	WREG32_OR(HDMI0_CONTROL + offset,
		  HDMI0_ERROR_ACK);

	WREG32_AND(HDMI0_INFOFRAME_CONTROL0 + offset,
		   ~HDMI0_AUDIO_INFO_SOURCE);

	r600_hdmi_update_audio_infoframe(encoder, buffer, sizeof(buffer));

	WREG32_OR(HDMI0_INFOFRAME_CONTROL0 + offset,
		  HDMI0_AUDIO_INFO_CONT |
		  HDMI0_AUDIO_INFO_UPDATE);
}