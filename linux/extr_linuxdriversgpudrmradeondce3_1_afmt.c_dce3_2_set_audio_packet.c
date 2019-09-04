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
typedef  scalar_t__ u32 ;
struct radeon_device {int dummy; } ;
struct drm_encoder {struct drm_device* dev; } ;
struct drm_device {struct radeon_device* dev_private; } ;

/* Variables and functions */
 int AFMT_60958_CS_UPDATE ; 
 scalar_t__ AFMT_AUDIO_PACKET_CONTROL ; 
 int AFMT_AUDIO_SAMPLE_SEND ; 
 int HDMI0_AUDIO_DELAY_EN (int) ; 
 int HDMI0_AUDIO_INFO_CONT ; 
 int HDMI0_AUDIO_INFO_LINE (int) ; 
 int HDMI0_AUDIO_INFO_SEND ; 
 int HDMI0_AUDIO_PACKETS_PER_LINE (int) ; 
 scalar_t__ HDMI0_AUDIO_PACKET_CONTROL ; 
 scalar_t__ HDMI0_INFOFRAME_CONTROL0 ; 
 scalar_t__ HDMI0_INFOFRAME_CONTROL1 ; 
 int /*<<< orphan*/  WREG32 (scalar_t__,int) ; 
 int /*<<< orphan*/  WREG32_OR (scalar_t__,int) ; 

void dce3_2_set_audio_packet(struct drm_encoder *encoder, u32 offset)
{
	struct drm_device *dev = encoder->dev;
	struct radeon_device *rdev = dev->dev_private;

	WREG32(HDMI0_AUDIO_PACKET_CONTROL + offset,
		HDMI0_AUDIO_DELAY_EN(1) |			/* default audio delay */
		HDMI0_AUDIO_PACKETS_PER_LINE(3));	/* should be suffient for all audio modes and small enough for all hblanks */

	WREG32(AFMT_AUDIO_PACKET_CONTROL + offset,
		AFMT_AUDIO_SAMPLE_SEND |			/* send audio packets */
		AFMT_60958_CS_UPDATE);				/* allow 60958 channel status fields to be updated */

	WREG32_OR(HDMI0_INFOFRAME_CONTROL0 + offset,
		HDMI0_AUDIO_INFO_SEND |				/* enable audio info frames (frames won't be set until audio is enabled) */
		HDMI0_AUDIO_INFO_CONT);				/* send audio info frames every frame/field */

	WREG32_OR(HDMI0_INFOFRAME_CONTROL1 + offset,
		HDMI0_AUDIO_INFO_LINE(2));			/* anything other than 0 */
}