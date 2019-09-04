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
typedef  int u8 ;
struct drm_dp_mst_topology_mgr {int /*<<< orphan*/  aux; } ;

/* Variables and functions */
 int DP_PAYLOAD_ACT_HANDLED ; 
 int /*<<< orphan*/  DP_PAYLOAD_TABLE_UPDATE_STATUS ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int,...) ; 
 int EINVAL ; 
 int drm_dp_dpcd_readb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  udelay (int) ; 

int drm_dp_check_act_status(struct drm_dp_mst_topology_mgr *mgr)
{
	u8 status;
	int ret;
	int count = 0;

	do {
		ret = drm_dp_dpcd_readb(mgr->aux, DP_PAYLOAD_TABLE_UPDATE_STATUS, &status);

		if (ret < 0) {
			DRM_DEBUG_KMS("failed to read payload table status %d\n", ret);
			goto fail;
		}

		if (status & DP_PAYLOAD_ACT_HANDLED)
			break;
		count++;
		udelay(100);

	} while (count < 30);

	if (!(status & DP_PAYLOAD_ACT_HANDLED)) {
		DRM_DEBUG_KMS("failed to get ACT bit %d after %d retries\n", status, count);
		ret = -EINVAL;
		goto fail;
	}
	return 0;
fail:
	return ret;
}