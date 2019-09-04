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
struct drm_connector {int dummy; } ;
struct cdn_dp_device {int /*<<< orphan*/  lock; scalar_t__ connected; } ;
typedef  enum drm_connector_status { ____Placeholder_drm_connector_status } drm_connector_status ;

/* Variables and functions */
 int connector_status_connected ; 
 int connector_status_disconnected ; 
 struct cdn_dp_device* connector_to_dp (struct drm_connector*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static enum drm_connector_status
cdn_dp_connector_detect(struct drm_connector *connector, bool force)
{
	struct cdn_dp_device *dp = connector_to_dp(connector);
	enum drm_connector_status status = connector_status_disconnected;

	mutex_lock(&dp->lock);
	if (dp->connected)
		status = connector_status_connected;
	mutex_unlock(&dp->lock);

	return status;
}