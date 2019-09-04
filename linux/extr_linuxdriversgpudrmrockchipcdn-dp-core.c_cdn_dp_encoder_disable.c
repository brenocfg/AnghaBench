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
struct drm_encoder {int dummy; } ;
struct cdn_dp_device {int /*<<< orphan*/  event_work; int /*<<< orphan*/  connected; int /*<<< orphan*/  lock; int /*<<< orphan*/  dev; scalar_t__ active; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ cdn_dp_connected_port (struct cdn_dp_device*) ; 
 int cdn_dp_disable (struct cdn_dp_device*) ; 
 struct cdn_dp_device* encoder_to_dp (struct drm_encoder*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cdn_dp_encoder_disable(struct drm_encoder *encoder)
{
	struct cdn_dp_device *dp = encoder_to_dp(encoder);
	int ret;

	mutex_lock(&dp->lock);
	if (dp->active) {
		ret = cdn_dp_disable(dp);
		if (ret) {
			DRM_DEV_ERROR(dp->dev, "Failed to disable encoder %d\n",
				      ret);
		}
	}
	mutex_unlock(&dp->lock);

	/*
	 * In the following 2 cases, we need to run the event_work to re-enable
	 * the DP:
	 * 1. If there is not just one port device is connected, and remove one
	 *    device from a port, the DP will be disabled here, at this case,
	 *    run the event_work to re-open DP for the other port.
	 * 2. If re-training or re-config failed, the DP will be disabled here.
	 *    run the event_work to re-connect it.
	 */
	if (!dp->connected && cdn_dp_connected_port(dp))
		schedule_work(&dp->event_work);
}