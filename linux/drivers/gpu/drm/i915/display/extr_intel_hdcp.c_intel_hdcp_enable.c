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
typedef  scalar_t__ u8 ;
struct intel_hdcp {scalar_t__ value; scalar_t__ content_type; int /*<<< orphan*/  mutex; int /*<<< orphan*/  prop_work; int /*<<< orphan*/  check_work; int /*<<< orphan*/  shim; } ;
struct intel_connector {struct intel_hdcp hdcp; } ;

/* Variables and functions */
 unsigned long DRM_HDCP2_CHECK_PERIOD_MS ; 
 unsigned long DRM_HDCP_CHECK_PERIOD_MS ; 
 scalar_t__ DRM_MODE_CONTENT_PROTECTION_ENABLED ; 
 scalar_t__ DRM_MODE_HDCP_CONTENT_TYPE1 ; 
 int EINVAL ; 
 int ENOENT ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int _intel_hdcp2_enable (struct intel_connector*) ; 
 int _intel_hdcp_enable (struct intel_connector*) ; 
 scalar_t__ intel_hdcp2_capable (struct intel_connector*) ; 
 scalar_t__ intel_hdcp_capable (struct intel_connector*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

int intel_hdcp_enable(struct intel_connector *connector, u8 content_type)
{
	struct intel_hdcp *hdcp = &connector->hdcp;
	unsigned long check_link_interval = DRM_HDCP_CHECK_PERIOD_MS;
	int ret = -EINVAL;

	if (!hdcp->shim)
		return -ENOENT;

	mutex_lock(&hdcp->mutex);
	WARN_ON(hdcp->value == DRM_MODE_CONTENT_PROTECTION_ENABLED);
	hdcp->content_type = content_type;

	/*
	 * Considering that HDCP2.2 is more secure than HDCP1.4, If the setup
	 * is capable of HDCP2.2, it is preferred to use HDCP2.2.
	 */
	if (intel_hdcp2_capable(connector)) {
		ret = _intel_hdcp2_enable(connector);
		if (!ret)
			check_link_interval = DRM_HDCP2_CHECK_PERIOD_MS;
	}

	/*
	 * When HDCP2.2 fails and Content Type is not Type1, HDCP1.4 will
	 * be attempted.
	 */
	if (ret && intel_hdcp_capable(connector) &&
	    hdcp->content_type != DRM_MODE_HDCP_CONTENT_TYPE1) {
		ret = _intel_hdcp_enable(connector);
	}

	if (!ret) {
		schedule_delayed_work(&hdcp->check_work, check_link_interval);
		hdcp->value = DRM_MODE_CONTENT_PROTECTION_ENABLED;
		schedule_work(&hdcp->prop_work);
	}

	mutex_unlock(&hdcp->mutex);
	return ret;
}