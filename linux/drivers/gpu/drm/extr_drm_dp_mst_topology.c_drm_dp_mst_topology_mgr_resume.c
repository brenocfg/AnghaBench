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
typedef  int /*<<< orphan*/  u8 ;
struct drm_dp_mst_topology_mgr {int /*<<< orphan*/  lock; scalar_t__ mst_primary; int /*<<< orphan*/  aux; int /*<<< orphan*/ * dpcd; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_DPCD_REV ; 
 int /*<<< orphan*/  DP_GUID ; 
 int /*<<< orphan*/  DP_MSTM_CTRL ; 
 int DP_MST_EN ; 
 int DP_RECEIVER_CAP_SIZE ; 
 int DP_UPSTREAM_IS_SRC ; 
 int DP_UP_REQ_EN ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 int /*<<< orphan*/  drm_dp_check_mstb_guid (scalar_t__,int /*<<< orphan*/ *) ; 
 int drm_dp_dpcd_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int drm_dp_dpcd_writeb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int drm_dp_mst_topology_mgr_resume(struct drm_dp_mst_topology_mgr *mgr)
{
	int ret = 0;

	mutex_lock(&mgr->lock);

	if (mgr->mst_primary) {
		int sret;
		u8 guid[16];

		sret = drm_dp_dpcd_read(mgr->aux, DP_DPCD_REV, mgr->dpcd, DP_RECEIVER_CAP_SIZE);
		if (sret != DP_RECEIVER_CAP_SIZE) {
			DRM_DEBUG_KMS("dpcd read failed - undocked during suspend?\n");
			ret = -1;
			goto out_unlock;
		}

		ret = drm_dp_dpcd_writeb(mgr->aux, DP_MSTM_CTRL,
					 DP_MST_EN | DP_UP_REQ_EN | DP_UPSTREAM_IS_SRC);
		if (ret < 0) {
			DRM_DEBUG_KMS("mst write failed - undocked during suspend?\n");
			ret = -1;
			goto out_unlock;
		}

		/* Some hubs forget their guids after they resume */
		sret = drm_dp_dpcd_read(mgr->aux, DP_GUID, guid, 16);
		if (sret != 16) {
			DRM_DEBUG_KMS("dpcd read failed - undocked during suspend?\n");
			ret = -1;
			goto out_unlock;
		}
		drm_dp_check_mstb_guid(mgr->mst_primary, guid);

		ret = 0;
	} else
		ret = -1;

out_unlock:
	mutex_unlock(&mgr->lock);
	return ret;
}