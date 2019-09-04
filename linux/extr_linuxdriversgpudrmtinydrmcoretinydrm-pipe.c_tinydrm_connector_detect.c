#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct drm_connector {int status; int /*<<< orphan*/  dev; } ;
typedef  enum drm_connector_status { ____Placeholder_drm_connector_status } drm_connector_status ;

/* Variables and functions */
 int connector_status_disconnected ; 
 scalar_t__ drm_dev_is_unplugged (int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum drm_connector_status
tinydrm_connector_detect(struct drm_connector *connector, bool force)
{
	if (drm_dev_is_unplugged(connector->dev))
		return connector_status_disconnected;

	return connector->status;
}