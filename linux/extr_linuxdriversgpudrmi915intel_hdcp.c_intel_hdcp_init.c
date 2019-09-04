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
struct intel_hdcp_shim {int dummy; } ;
struct intel_connector {int /*<<< orphan*/  hdcp_prop_work; int /*<<< orphan*/  hdcp_check_work; int /*<<< orphan*/  hdcp_mutex; struct intel_hdcp_shim const* hdcp_shim; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int drm_connector_attach_content_protection_property (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_hdcp_check_work ; 
 int /*<<< orphan*/  intel_hdcp_prop_work ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

int intel_hdcp_init(struct intel_connector *connector,
		    const struct intel_hdcp_shim *hdcp_shim)
{
	int ret;

	ret = drm_connector_attach_content_protection_property(
			&connector->base);
	if (ret)
		return ret;

	connector->hdcp_shim = hdcp_shim;
	mutex_init(&connector->hdcp_mutex);
	INIT_DELAYED_WORK(&connector->hdcp_check_work, intel_hdcp_check_work);
	INIT_WORK(&connector->hdcp_prop_work, intel_hdcp_prop_work);
	return 0;
}