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
struct analogix_dp_device {TYPE_1__* plat_data; } ;
typedef  enum drm_connector_status { ____Placeholder_drm_connector_status } drm_connector_status ;
struct TYPE_2__ {scalar_t__ panel; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int /*<<< orphan*/  analogix_dp_detect_hpd (struct analogix_dp_device*) ; 
 int analogix_dp_prepare_panel (struct analogix_dp_device*,int,int) ; 
 int connector_status_connected ; 
 int connector_status_disconnected ; 
 struct analogix_dp_device* to_dp (struct drm_connector*) ; 

__attribute__((used)) static enum drm_connector_status
analogix_dp_detect(struct drm_connector *connector, bool force)
{
	struct analogix_dp_device *dp = to_dp(connector);
	enum drm_connector_status status = connector_status_disconnected;
	int ret;

	if (dp->plat_data->panel)
		return connector_status_connected;

	ret = analogix_dp_prepare_panel(dp, true, false);
	if (ret) {
		DRM_ERROR("Failed to prepare panel (%d)\n", ret);
		return connector_status_disconnected;
	}

	if (!analogix_dp_detect_hpd(dp))
		status = connector_status_connected;

	ret = analogix_dp_prepare_panel(dp, false, false);
	if (ret)
		DRM_ERROR("Failed to unprepare panel (%d)\n", ret);

	return status;
}