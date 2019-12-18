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
struct radeon_device {int dummy; } ;
struct drm_device {int max_vblank_count; struct radeon_device* dev_private; } ;

/* Variables and functions */
 scalar_t__ ASIC_IS_AVIVO (struct radeon_device*) ; 

int radeon_driver_irq_postinstall_kms(struct drm_device *dev)
{
	struct radeon_device *rdev = dev->dev_private;

	if (ASIC_IS_AVIVO(rdev))
		dev->max_vblank_count = 0x00ffffff;
	else
		dev->max_vblank_count = 0x001fffff;

	return 0;
}