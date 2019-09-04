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
struct drm_device {TYPE_1__* primary; } ;
struct drm_connector {int /*<<< orphan*/  kdev; int /*<<< orphan*/  name; struct drm_device* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  index; int /*<<< orphan*/  kdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  connector_dev_groups ; 
 int /*<<< orphan*/  device_create_with_groups (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct drm_connector*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_class ; 
 int /*<<< orphan*/  drm_sysfs_hotplug_event (struct drm_device*) ; 

int drm_sysfs_connector_add(struct drm_connector *connector)
{
	struct drm_device *dev = connector->dev;

	if (connector->kdev)
		return 0;

	connector->kdev =
		device_create_with_groups(drm_class, dev->primary->kdev, 0,
					  connector, connector_dev_groups,
					  "card%d-%s", dev->primary->index,
					  connector->name);
	DRM_DEBUG("adding \"%s\" to sysfs\n",
		  connector->name);

	if (IS_ERR(connector->kdev)) {
		DRM_ERROR("failed to register connector device: %ld\n", PTR_ERR(connector->kdev));
		return PTR_ERR(connector->kdev);
	}

	/* Let userspace know we have a new connector */
	drm_sysfs_hotplug_event(dev);

	return 0;
}