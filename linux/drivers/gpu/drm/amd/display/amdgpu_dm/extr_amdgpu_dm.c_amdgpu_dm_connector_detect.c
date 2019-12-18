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
struct drm_connector {int dummy; } ;
struct TYPE_2__ {scalar_t__ force; } ;
struct amdgpu_dm_connector {TYPE_1__ base; int /*<<< orphan*/ * dc_sink; int /*<<< orphan*/  fake_enable; } ;
typedef  enum drm_connector_status { ____Placeholder_drm_connector_status } drm_connector_status ;

/* Variables and functions */
 scalar_t__ DRM_FORCE_ON ; 
 scalar_t__ DRM_FORCE_UNSPECIFIED ; 
 int connector_status_connected ; 
 int connector_status_disconnected ; 
 struct amdgpu_dm_connector* to_amdgpu_dm_connector (struct drm_connector*) ; 

__attribute__((used)) static enum drm_connector_status
amdgpu_dm_connector_detect(struct drm_connector *connector, bool force)
{
	bool connected;
	struct amdgpu_dm_connector *aconnector = to_amdgpu_dm_connector(connector);

	/*
	 * Notes:
	 * 1. This interface is NOT called in context of HPD irq.
	 * 2. This interface *is called* in context of user-mode ioctl. Which
	 * makes it a bad place for *any* MST-related activity.
	 */

	if (aconnector->base.force == DRM_FORCE_UNSPECIFIED &&
	    !aconnector->fake_enable)
		connected = (aconnector->dc_sink != NULL);
	else
		connected = (aconnector->base.force == DRM_FORCE_ON);

	return (connected ? connector_status_connected :
			connector_status_disconnected);
}