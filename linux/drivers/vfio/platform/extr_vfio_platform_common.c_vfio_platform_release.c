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
struct vfio_platform_device {int /*<<< orphan*/  parent_module; int /*<<< orphan*/  device; scalar_t__ reset_required; int /*<<< orphan*/  refcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int,char const*) ; 
 int /*<<< orphan*/  driver_lock ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ ) ; 
 int vfio_platform_call_reset (struct vfio_platform_device*,char const**) ; 
 int /*<<< orphan*/  vfio_platform_irq_cleanup (struct vfio_platform_device*) ; 
 int /*<<< orphan*/  vfio_platform_regions_cleanup (struct vfio_platform_device*) ; 

__attribute__((used)) static void vfio_platform_release(void *device_data)
{
	struct vfio_platform_device *vdev = device_data;

	mutex_lock(&driver_lock);

	if (!(--vdev->refcnt)) {
		const char *extra_dbg = NULL;
		int ret;

		ret = vfio_platform_call_reset(vdev, &extra_dbg);
		if (ret && vdev->reset_required) {
			dev_warn(vdev->device, "reset driver is required and reset call failed in release (%d) %s\n",
				 ret, extra_dbg ? extra_dbg : "");
			WARN_ON(1);
		}
		pm_runtime_put(vdev->device);
		vfio_platform_regions_cleanup(vdev);
		vfio_platform_irq_cleanup(vdev);
	}

	mutex_unlock(&driver_lock);

	module_put(vdev->parent_module);
}