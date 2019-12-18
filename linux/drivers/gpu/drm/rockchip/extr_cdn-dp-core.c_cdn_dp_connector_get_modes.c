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
struct edid {int /*<<< orphan*/  height_cm; int /*<<< orphan*/  width_cm; } ;
struct drm_connector {int dummy; } ;
struct cdn_dp_device {int /*<<< orphan*/  lock; int /*<<< orphan*/  sink_has_audio; int /*<<< orphan*/  dev; struct edid* edid; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_DEBUG_KMS (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct cdn_dp_device* connector_to_dp (struct drm_connector*) ; 
 int drm_add_edid_modes (struct drm_connector*,struct edid*) ; 
 int /*<<< orphan*/  drm_connector_update_edid_property (struct drm_connector*,struct edid*) ; 
 int /*<<< orphan*/  drm_detect_monitor_audio (struct edid*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cdn_dp_connector_get_modes(struct drm_connector *connector)
{
	struct cdn_dp_device *dp = connector_to_dp(connector);
	struct edid *edid;
	int ret = 0;

	mutex_lock(&dp->lock);
	edid = dp->edid;
	if (edid) {
		DRM_DEV_DEBUG_KMS(dp->dev, "got edid: width[%d] x height[%d]\n",
				  edid->width_cm, edid->height_cm);

		dp->sink_has_audio = drm_detect_monitor_audio(edid);
		ret = drm_add_edid_modes(connector, edid);
		if (ret)
			drm_connector_update_edid_property(connector,
								edid);
	}
	mutex_unlock(&dp->lock);

	return ret;
}