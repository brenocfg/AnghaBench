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
struct drm_connector {int registered; int /*<<< orphan*/  mutex; TYPE_1__* funcs; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* early_unregister ) (struct drm_connector*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  drm_debugfs_connector_remove (struct drm_connector*) ; 
 int /*<<< orphan*/  drm_sysfs_connector_remove (struct drm_connector*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct drm_connector*) ; 

void drm_connector_unregister(struct drm_connector *connector)
{
	mutex_lock(&connector->mutex);
	if (!connector->registered) {
		mutex_unlock(&connector->mutex);
		return;
	}

	if (connector->funcs->early_unregister)
		connector->funcs->early_unregister(connector);

	drm_sysfs_connector_remove(connector);
	drm_debugfs_connector_remove(connector);

	connector->registered = false;
	mutex_unlock(&connector->mutex);
}