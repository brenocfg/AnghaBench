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
struct drm_connector {TYPE_1__* kdev; int /*<<< orphan*/  name; scalar_t__ ddc; } ;
struct TYPE_2__ {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_unregister (TYPE_1__*) ; 
 int /*<<< orphan*/  sysfs_remove_link (int /*<<< orphan*/ *,char*) ; 

void drm_sysfs_connector_remove(struct drm_connector *connector)
{
	if (!connector->kdev)
		return;

	if (connector->ddc)
		sysfs_remove_link(&connector->kdev->kobj, "ddc");

	DRM_DEBUG("removing \"%s\" from sysfs\n",
		  connector->name);

	device_unregister(connector->kdev);
	connector->kdev = NULL;
}