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
struct drm_device {int /*<<< orphan*/ * sg; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_LEGACY ; 
 int /*<<< orphan*/  DRIVER_SG ; 
 scalar_t__ drm_core_check_feature (struct drm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_sg_cleanup (int /*<<< orphan*/ *) ; 

void drm_legacy_sg_cleanup(struct drm_device *dev)
{
	if (drm_core_check_feature(dev, DRIVER_SG) && dev->sg &&
	    drm_core_check_feature(dev, DRIVER_LEGACY)) {
		drm_sg_cleanup(dev->sg);
		dev->sg = NULL;
	}
}