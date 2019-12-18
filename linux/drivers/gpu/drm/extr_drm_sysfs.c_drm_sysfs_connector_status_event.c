#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int id; } ;
struct drm_property {TYPE_1__ base; } ;
struct drm_device {TYPE_3__* primary; } ;
struct TYPE_8__ {int id; } ;
struct drm_connector {TYPE_4__ base; struct drm_device* dev; } ;
struct TYPE_7__ {TYPE_2__* kdev; } ;
struct TYPE_6__ {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (char*) ; 
 int /*<<< orphan*/  DRM_DEBUG (char*) ; 
 int /*<<< orphan*/  KOBJ_CHANGE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  drm_mode_obj_find_prop_id (TYPE_4__*,int) ; 
 int /*<<< orphan*/  kobject_uevent_env (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,int) ; 

void drm_sysfs_connector_status_event(struct drm_connector *connector,
				      struct drm_property *property)
{
	struct drm_device *dev = connector->dev;
	char hotplug_str[] = "HOTPLUG=1", conn_id[21], prop_id[21];
	char *envp[4] = { hotplug_str, conn_id, prop_id, NULL };

	WARN_ON(!drm_mode_obj_find_prop_id(&connector->base,
					   property->base.id));

	snprintf(conn_id, ARRAY_SIZE(conn_id),
		 "CONNECTOR=%u", connector->base.id);
	snprintf(prop_id, ARRAY_SIZE(prop_id),
		 "PROPERTY=%u", property->base.id);

	DRM_DEBUG("generating connector status event\n");

	kobject_uevent_env(&dev->primary->kdev->kobj, KOBJ_CHANGE, envp);
}