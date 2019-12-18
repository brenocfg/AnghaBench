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
 scalar_t__ HDMI0_60958_0 ; 
 scalar_t__ HDMI0_60958_1 ; 
 int HDMI0_60958_CS_CHANNEL_NUMBER_L (int) ; 
 int HDMI0_60958_CS_CHANNEL_NUMBER_L_MASK ; 
 int HDMI0_60958_CS_CHANNEL_NUMBER_R (int) ; 
 int HDMI0_60958_CS_CHANNEL_NUMBER_R_MASK ; 
 int HDMI0_60958_CS_CLOCK_ACCURACY_MASK ; 
 int HDMI0_60958_CS_UPDATE ; 
 int HDMI0_AUDIO_DELAY_EN (int) ; 
 int HDMI0_AUDIO_DELAY_EN_MASK ; 
 int HDMI0_AUDIO_INFO_LINE (int) ; 
 int HDMI0_AUDIO_INFO_LINE_MASK ; 
 int HDMI0_AUDIO_INFO_SEND ; 
 int HDMI0_AUDIO_INFO_UPDATE ; 
 int HDMI0_AUDIO_PACKETS_PER_LINE (int) ; 
 int HDMI0_AUDIO_PACKETS_PER_LINE_MASK ; 
 scalar_t__ HDMI0_AUDIO_PACKET_CONTROL ; 
 int HDMI0_AUDIO_SAMPLE_SEND ; 
 int HDMI0_GENERIC0_CONT ; 
 int HDMI0_GENERIC0_LINE_MASK ; 
 int HDMI0_GENERIC0_SEND ; 
 int HDMI0_GENERIC0_UPDATE ; 
 int HDMI0_GENERIC1_CONT ; 
 int HDMI0_GENERIC1_LINE_MASK ; 
 int HDMI0_GENERIC1_SEND ; 
 scalar_t__ HDMI0_GENERIC_PACKET_CONTROL ; 
 scalar_t__ HDMI0_INFOFRAME_CONTROL0 ; 
 scalar_t__ HDMI0_INFOFRAME_CONTROL1 ; 
 int /*<<< orphan*/  WREG32_AND (scalar_t__,int) ; 
 int /*<<< orphan*/  WREG32_OR (scalar_t__,int) ; 
 int /*<<< orphan*/  WREG32_P (scalar_t__,int,int) ; 

void r600_set_audio_packet(struct drm_encoder *encoder, u32 offset)
{
	struct drm_device *dev = encoder->dev;
	struct radeon_device *rdev = dev->dev_private;

	WREG32_P(HDMI0_AUDIO_PACKET_CONTROL + offset,
		HDMI0_AUDIO_SAMPLE_SEND |			/* send audio packets */
		HDMI0_AUDIO_DELAY_EN(1) |			/* default audio delay */
		HDMI0_AUDIO_PACKETS_PER_LINE(3) |	/* should be suffient for all audio modes and small enough for all hblanks */
		HDMI0_60958_CS_UPDATE,				/* allow 60958 channel status fields to be updated */
		~(HDMI0_AUDIO_SAMPLE_SEND |
		HDMI0_AUDIO_DELAY_EN_MASK |
		HDMI0_AUDIO_PACKETS_PER_LINE_MASK |
		HDMI0_60958_CS_UPDATE));

	WREG32_OR(HDMI0_INFOFRAME_CONTROL0 + offset,
		HDMI0_AUDIO_INFO_SEND |		/* enable audio info frames (frames won't be set until audio is enabled) */
		HDMI0_AUDIO_INFO_UPDATE);	/* required for audio info values to be updated */

	WREG32_P(HDMI0_INFOFRAME_CONTROL1 + offset,
		HDMI0_AUDIO_INFO_LINE(2),	/* anything other than 0 */
		~HDMI0_AUDIO_INFO_LINE_MASK);

	WREG32_AND(HDMI0_GENERIC_PACKET_CONTROL + offset,
		~(HDMI0_GENERIC0_SEND |
		HDMI0_GENERIC0_CONT |
		HDMI0_GENERIC0_UPDATE |
		HDMI0_GENERIC1_SEND |
		HDMI0_GENERIC1_CONT |
		HDMI0_GENERIC0_LINE_MASK |
		HDMI0_GENERIC1_LINE_MASK));

	WREG32_P(HDMI0_60958_0 + offset,
		HDMI0_60958_CS_CHANNEL_NUMBER_L(1),
		~(HDMI0_60958_CS_CHANNEL_NUMBER_L_MASK |
		HDMI0_60958_CS_CLOCK_ACCURACY_MASK));

	WREG32_P(HDMI0_60958_1 + offset,
		HDMI0_60958_CS_CHANNEL_NUMBER_R(2),
		~HDMI0_60958_CS_CHANNEL_NUMBER_R_MASK);
}