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
struct TYPE_2__ {int default_dispclk; } ;
struct radeon_device {TYPE_1__ clock; } ;
struct drm_device {struct radeon_device* dev_private; } ;
struct drm_connector {struct drm_device* dev; } ;

/* Variables and functions */
 scalar_t__ ASIC_IS_DCE5 (struct radeon_device*) ; 
 scalar_t__ radeon_connector_encoder_is_hbr2 (struct drm_connector*) ; 

bool radeon_connector_is_dp12_capable(struct drm_connector *connector)
{
	struct drm_device *dev = connector->dev;
	struct radeon_device *rdev = dev->dev_private;

	if (ASIC_IS_DCE5(rdev) &&
	    (rdev->clock.default_dispclk >= 53900) &&
	    radeon_connector_encoder_is_hbr2(connector)) {
		return true;
	}

	return false;
}