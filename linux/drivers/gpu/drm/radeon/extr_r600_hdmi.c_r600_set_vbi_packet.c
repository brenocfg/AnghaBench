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
 int HDMI0_GC_CONT ; 
 int HDMI0_GC_SEND ; 
 int HDMI0_NULL_SEND ; 
 scalar_t__ HDMI0_VBI_PACKET_CONTROL ; 
 int /*<<< orphan*/  WREG32_OR (scalar_t__,int) ; 

void r600_set_vbi_packet(struct drm_encoder *encoder, u32 offset)
{
	struct drm_device *dev = encoder->dev;
	struct radeon_device *rdev = dev->dev_private;

	WREG32_OR(HDMI0_VBI_PACKET_CONTROL + offset,
		HDMI0_NULL_SEND |	/* send null packets when required */
		HDMI0_GC_SEND |		/* send general control packets */
		HDMI0_GC_CONT);		/* send general control packets every frame */
}