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
struct intel_fbdev {int /*<<< orphan*/  cookie; } ;
struct drm_device {int dummy; } ;
struct TYPE_2__ {struct intel_fbdev* fbdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  async_schedule (int /*<<< orphan*/ ,struct intel_fbdev*) ; 
 int /*<<< orphan*/  intel_fbdev_initial_config ; 
 TYPE_1__* to_i915 (struct drm_device*) ; 

void intel_fbdev_initial_config_async(struct drm_device *dev)
{
	struct intel_fbdev *ifbdev = to_i915(dev)->fbdev;

	if (!ifbdev)
		return;

	ifbdev->cookie = async_schedule(intel_fbdev_initial_config, ifbdev);
}