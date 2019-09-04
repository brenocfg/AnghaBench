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
struct cdn_dp_device {int /*<<< orphan*/  connector; int /*<<< orphan*/  edid; int /*<<< orphan*/  dev; int /*<<< orphan*/  dpcd; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_DPCD_REV ; 
 int /*<<< orphan*/  DP_RECEIVER_CAP_SIZE ; 
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ ,char*,int) ; 
 int ENODEV ; 
 int /*<<< orphan*/  cdn_dp_check_sink_connection (struct cdn_dp_device*) ; 
 int cdn_dp_dpcd_read (struct cdn_dp_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cdn_dp_get_edid_block ; 
 int /*<<< orphan*/  drm_do_get_edid (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct cdn_dp_device*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cdn_dp_get_sink_capability(struct cdn_dp_device *dp)
{
	int ret;

	if (!cdn_dp_check_sink_connection(dp))
		return -ENODEV;

	ret = cdn_dp_dpcd_read(dp, DP_DPCD_REV, dp->dpcd,
			       DP_RECEIVER_CAP_SIZE);
	if (ret) {
		DRM_DEV_ERROR(dp->dev, "Failed to get caps %d\n", ret);
		return ret;
	}

	kfree(dp->edid);
	dp->edid = drm_do_get_edid(&dp->connector,
				   cdn_dp_get_edid_block, dp);
	return 0;
}