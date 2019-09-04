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
struct intel_connector {int /*<<< orphan*/  hdcp_mutex; int /*<<< orphan*/  hdcp_check_work; int /*<<< orphan*/  hdcp_prop_work; int /*<<< orphan*/  hdcp_value; int /*<<< orphan*/  hdcp_shim; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_HDCP_CHECK_PERIOD_MS ; 
 int /*<<< orphan*/  DRM_MODE_CONTENT_PROTECTION_ENABLED ; 
 int ENOENT ; 
 int _intel_hdcp_enable (struct intel_connector*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

int intel_hdcp_enable(struct intel_connector *connector)
{
	int ret;

	if (!connector->hdcp_shim)
		return -ENOENT;

	mutex_lock(&connector->hdcp_mutex);

	ret = _intel_hdcp_enable(connector);
	if (ret)
		goto out;

	connector->hdcp_value = DRM_MODE_CONTENT_PROTECTION_ENABLED;
	schedule_work(&connector->hdcp_prop_work);
	schedule_delayed_work(&connector->hdcp_check_work,
			      DRM_HDCP_CHECK_PERIOD_MS);
out:
	mutex_unlock(&connector->hdcp_mutex);
	return ret;
}