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
struct intel_connector {scalar_t__ hdcp_value; int /*<<< orphan*/  hdcp_check_work; int /*<<< orphan*/  hdcp_mutex; int /*<<< orphan*/  hdcp_shim; } ;

/* Variables and functions */
 scalar_t__ DRM_MODE_CONTENT_PROTECTION_UNDESIRED ; 
 int ENOENT ; 
 int _intel_hdcp_disable (struct intel_connector*) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int intel_hdcp_disable(struct intel_connector *connector)
{
	int ret = 0;

	if (!connector->hdcp_shim)
		return -ENOENT;

	mutex_lock(&connector->hdcp_mutex);

	if (connector->hdcp_value != DRM_MODE_CONTENT_PROTECTION_UNDESIRED) {
		connector->hdcp_value = DRM_MODE_CONTENT_PROTECTION_UNDESIRED;
		ret = _intel_hdcp_disable(connector);
	}

	mutex_unlock(&connector->hdcp_mutex);
	cancel_delayed_work_sync(&connector->hdcp_check_work);
	return ret;
}