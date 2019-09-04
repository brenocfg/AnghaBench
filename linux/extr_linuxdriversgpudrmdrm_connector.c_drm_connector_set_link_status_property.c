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
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_4__ {int /*<<< orphan*/  connection_mutex; } ;
struct drm_device {TYPE_2__ mode_config; } ;
struct drm_connector {TYPE_1__* state; struct drm_device* dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  link_status; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_modeset_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_modeset_unlock (int /*<<< orphan*/ *) ; 

void drm_connector_set_link_status_property(struct drm_connector *connector,
					    uint64_t link_status)
{
	struct drm_device *dev = connector->dev;

	drm_modeset_lock(&dev->mode_config.connection_mutex, NULL);
	connector->state->link_status = link_status;
	drm_modeset_unlock(&dev->mode_config.connection_mutex);
}