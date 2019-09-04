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
struct drm_connector {TYPE_1__* dev; } ;
struct dc_link {int dummy; } ;
struct amdgpu_dm_connector {struct dc_link* dc_link; } ;
struct amdgpu_display_manager {int dummy; } ;
struct amdgpu_device {struct amdgpu_display_manager dm; } ;
struct TYPE_2__ {struct amdgpu_device* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_connector_cleanup (struct drm_connector*) ; 
 int /*<<< orphan*/  drm_connector_unregister (struct drm_connector*) ; 
 int /*<<< orphan*/  kfree (struct drm_connector*) ; 
 struct amdgpu_dm_connector* to_amdgpu_dm_connector (struct drm_connector*) ; 

__attribute__((used)) static void amdgpu_dm_connector_destroy(struct drm_connector *connector)
{
	struct amdgpu_dm_connector *aconnector = to_amdgpu_dm_connector(connector);
	const struct dc_link *link = aconnector->dc_link;
	struct amdgpu_device *adev = connector->dev->dev_private;
	struct amdgpu_display_manager *dm = &adev->dm;

#if defined(CONFIG_BACKLIGHT_CLASS_DEVICE) ||\
	defined(CONFIG_BACKLIGHT_CLASS_DEVICE_MODULE)

	if ((link->connector_signal & (SIGNAL_TYPE_EDP | SIGNAL_TYPE_LVDS)) &&
	    link->type != dc_connection_none &&
	    dm->backlight_dev) {
		backlight_device_unregister(dm->backlight_dev);
		dm->backlight_dev = NULL;
	}
#endif
	drm_connector_unregister(connector);
	drm_connector_cleanup(connector);
	kfree(connector);
}