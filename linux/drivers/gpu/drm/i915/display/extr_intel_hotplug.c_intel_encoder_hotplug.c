#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct intel_encoder {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  id; } ;
struct TYPE_6__ {int status; int /*<<< orphan*/  name; TYPE_2__ base; struct drm_device* dev; } ;
struct intel_connector {TYPE_3__ base; } ;
struct TYPE_4__ {int /*<<< orphan*/  mutex; } ;
struct drm_device {TYPE_1__ mode_config; } ;
typedef  enum intel_hotplug_state { ____Placeholder_intel_hotplug_state } intel_hotplug_state ;
typedef  enum drm_connector_status { ____Placeholder_drm_connector_status } drm_connector_status ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int INTEL_HOTPLUG_CHANGED ; 
 int INTEL_HOTPLUG_UNCHANGED ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  drm_get_connector_status_name (int) ; 
 int drm_helper_probe_detect (TYPE_3__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mutex_is_locked (int /*<<< orphan*/ *) ; 

enum intel_hotplug_state
intel_encoder_hotplug(struct intel_encoder *encoder,
		      struct intel_connector *connector,
		      bool irq_received)
{
	struct drm_device *dev = connector->base.dev;
	enum drm_connector_status old_status;

	WARN_ON(!mutex_is_locked(&dev->mode_config.mutex));
	old_status = connector->base.status;

	connector->base.status =
		drm_helper_probe_detect(&connector->base, NULL, false);

	if (old_status == connector->base.status)
		return INTEL_HOTPLUG_UNCHANGED;

	DRM_DEBUG_KMS("[CONNECTOR:%d:%s] status updated from %s to %s\n",
		      connector->base.base.id,
		      connector->base.name,
		      drm_get_connector_status_name(old_status),
		      drm_get_connector_status_name(connector->base.status));

	return INTEL_HOTPLUG_CHANGED;
}