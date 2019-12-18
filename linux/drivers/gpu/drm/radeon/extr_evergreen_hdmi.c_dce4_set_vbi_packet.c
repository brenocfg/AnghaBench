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
 int HDMI_GC_CONT ; 
 int HDMI_GC_SEND ; 
 int HDMI_NULL_SEND ; 
 scalar_t__ HDMI_VBI_PACKET_CONTROL ; 
 int /*<<< orphan*/  WREG32 (scalar_t__,int) ; 

void dce4_set_vbi_packet(struct drm_encoder *encoder, u32 offset)
{
	struct drm_device *dev = encoder->dev;
	struct radeon_device *rdev = dev->dev_private;

	WREG32(HDMI_VBI_PACKET_CONTROL + offset,
		HDMI_NULL_SEND |	/* send null packets when required */
		HDMI_GC_SEND |		/* send general control packets */
		HDMI_GC_CONT);		/* send general control packets every frame */
}