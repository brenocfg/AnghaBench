#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct drm_device {struct amdgpu_device* dev_private; } ;
struct drm_connector {struct drm_device* dev; } ;
struct TYPE_4__ {TYPE_1__* rfbdev; } ;
struct amdgpu_device {TYPE_2__ mode_info; } ;
struct TYPE_3__ {int /*<<< orphan*/  helper; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  drm_connector_register (struct drm_connector*) ; 
 int /*<<< orphan*/  drm_fb_helper_add_one_connector (int /*<<< orphan*/ *,struct drm_connector*) ; 

__attribute__((used)) static void dm_dp_mst_register_connector(struct drm_connector *connector)
{
	struct drm_device *dev = connector->dev;
	struct amdgpu_device *adev = dev->dev_private;

	if (adev->mode_info.rfbdev)
		drm_fb_helper_add_one_connector(&adev->mode_info.rfbdev->helper, connector);
	else
		DRM_ERROR("adev->mode_info.rfbdev is NULL\n");

	drm_connector_register(connector);
}