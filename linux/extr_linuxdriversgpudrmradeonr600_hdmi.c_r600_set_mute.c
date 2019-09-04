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
 scalar_t__ HDMI0_GC ; 
 int /*<<< orphan*/  HDMI0_GC_AVMUTE ; 
 int /*<<< orphan*/  WREG32_AND (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32_OR (scalar_t__,int /*<<< orphan*/ ) ; 

void r600_set_mute(struct drm_encoder *encoder, u32 offset, bool mute)
{
	struct drm_device *dev = encoder->dev;
	struct radeon_device *rdev = dev->dev_private;

	if (mute)
		WREG32_OR(HDMI0_GC + offset, HDMI0_GC_AVMUTE);
	else
		WREG32_AND(HDMI0_GC + offset, ~HDMI0_GC_AVMUTE);
}