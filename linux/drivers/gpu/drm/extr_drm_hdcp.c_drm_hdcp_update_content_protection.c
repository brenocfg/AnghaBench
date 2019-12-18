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
typedef  scalar_t__ u64 ;
struct TYPE_2__ {int /*<<< orphan*/  content_protection_property; int /*<<< orphan*/  connection_mutex; } ;
struct drm_device {TYPE_1__ mode_config; } ;
struct drm_connector_state {scalar_t__ content_protection; } ;
struct drm_connector {struct drm_connector_state* state; struct drm_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  drm_modeset_is_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_sysfs_connector_status_event (struct drm_connector*,int /*<<< orphan*/ ) ; 

void drm_hdcp_update_content_protection(struct drm_connector *connector,
					u64 val)
{
	struct drm_device *dev = connector->dev;
	struct drm_connector_state *state = connector->state;

	WARN_ON(!drm_modeset_is_locked(&dev->mode_config.connection_mutex));
	if (state->content_protection == val)
		return;

	state->content_protection = val;
	drm_sysfs_connector_status_event(connector,
				 dev->mode_config.content_protection_property);
}