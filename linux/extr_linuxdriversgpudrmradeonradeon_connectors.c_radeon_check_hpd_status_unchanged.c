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
struct radeon_device {scalar_t__ family; } ;
struct TYPE_2__ {scalar_t__ hpd; } ;
struct radeon_connector {TYPE_1__ hpd; } ;
struct drm_device {struct radeon_device* dev_private; } ;
struct drm_connector {int status; struct drm_device* dev; } ;
typedef  enum drm_connector_status { ____Placeholder_drm_connector_status } drm_connector_status ;

/* Variables and functions */
 scalar_t__ CHIP_R600 ; 
 scalar_t__ RADEON_HPD_NONE ; 
 int connector_status_connected ; 
 int connector_status_disconnected ; 
 scalar_t__ radeon_hpd_sense (struct radeon_device*,scalar_t__) ; 
 struct radeon_connector* to_radeon_connector (struct drm_connector*) ; 

__attribute__((used)) static bool radeon_check_hpd_status_unchanged(struct drm_connector *connector)
{
	struct drm_device *dev = connector->dev;
	struct radeon_device *rdev = dev->dev_private;
	struct radeon_connector *radeon_connector = to_radeon_connector(connector);
	enum drm_connector_status status;

	/* We only trust HPD on R600 and newer ASICS. */
	if (rdev->family >= CHIP_R600
	  && radeon_connector->hpd.hpd != RADEON_HPD_NONE) {
		if (radeon_hpd_sense(rdev, radeon_connector->hpd.hpd))
			status = connector_status_connected;
		else
			status = connector_status_disconnected;
		if (connector->status == status)
			return true;
	}

	return false;
}