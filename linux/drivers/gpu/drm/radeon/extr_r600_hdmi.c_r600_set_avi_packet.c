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
typedef  int uint8_t ;
typedef  scalar_t__ u32 ;
struct radeon_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ HDMI0_AVI_INFO0 ; 
 scalar_t__ HDMI0_AVI_INFO1 ; 
 scalar_t__ HDMI0_AVI_INFO2 ; 
 scalar_t__ HDMI0_AVI_INFO3 ; 
 int HDMI0_AVI_INFO_CONT ; 
 int HDMI0_AVI_INFO_LINE (int) ; 
 int HDMI0_AVI_INFO_SEND ; 
 scalar_t__ HDMI0_INFOFRAME_CONTROL0 ; 
 scalar_t__ HDMI0_INFOFRAME_CONTROL1 ; 
 int /*<<< orphan*/  WREG32 (scalar_t__,int) ; 
 int /*<<< orphan*/  WREG32_OR (scalar_t__,int) ; 

void r600_set_avi_packet(struct radeon_device *rdev, u32 offset,
			 unsigned char *buffer, size_t size)
{
	uint8_t *frame = buffer + 3;

	WREG32(HDMI0_AVI_INFO0 + offset,
		frame[0x0] | (frame[0x1] << 8) | (frame[0x2] << 16) | (frame[0x3] << 24));
	WREG32(HDMI0_AVI_INFO1 + offset,
		frame[0x4] | (frame[0x5] << 8) | (frame[0x6] << 16) | (frame[0x7] << 24));
	WREG32(HDMI0_AVI_INFO2 + offset,
		frame[0x8] | (frame[0x9] << 8) | (frame[0xA] << 16) | (frame[0xB] << 24));
	WREG32(HDMI0_AVI_INFO3 + offset,
		frame[0xC] | (frame[0xD] << 8) | (buffer[1] << 24));

	WREG32_OR(HDMI0_INFOFRAME_CONTROL1 + offset,
		  HDMI0_AVI_INFO_LINE(2));	/* anything other than 0 */

	WREG32_OR(HDMI0_INFOFRAME_CONTROL0 + offset,
		  HDMI0_AVI_INFO_SEND |	/* enable AVI info frames */
		  HDMI0_AVI_INFO_CONT);	/* send AVI info frames every frame/field */

}