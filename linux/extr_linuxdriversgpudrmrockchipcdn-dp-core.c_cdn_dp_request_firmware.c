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
struct cdn_dp_device {int fw_loaded; int /*<<< orphan*/  lock; int /*<<< orphan*/  dev; int /*<<< orphan*/  fw; } ;

/* Variables and functions */
 int /*<<< orphan*/  CDN_DP_FIRMWARE ; 
 int /*<<< orphan*/  CDN_FW_TIMEOUT_MS ; 
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ ,char*,...) ; 
 int ENOENT ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (unsigned long) ; 
 int /*<<< orphan*/  mutex_is_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int request_firmware (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 

__attribute__((used)) static int cdn_dp_request_firmware(struct cdn_dp_device *dp)
{
	int ret;
	unsigned long timeout = jiffies + msecs_to_jiffies(CDN_FW_TIMEOUT_MS);
	unsigned long sleep = 1000;

	WARN_ON(!mutex_is_locked(&dp->lock));

	if (dp->fw_loaded)
		return 0;

	/* Drop the lock before getting the firmware to avoid blocking boot */
	mutex_unlock(&dp->lock);

	while (time_before(jiffies, timeout)) {
		ret = request_firmware(&dp->fw, CDN_DP_FIRMWARE, dp->dev);
		if (ret == -ENOENT) {
			msleep(sleep);
			sleep *= 2;
			continue;
		} else if (ret) {
			DRM_DEV_ERROR(dp->dev,
				      "failed to request firmware: %d\n", ret);
			goto out;
		}

		dp->fw_loaded = true;
		ret = 0;
		goto out;
	}

	DRM_DEV_ERROR(dp->dev, "Timed out trying to load firmware\n");
	ret = -ETIMEDOUT;
out:
	mutex_lock(&dp->lock);
	return ret;
}