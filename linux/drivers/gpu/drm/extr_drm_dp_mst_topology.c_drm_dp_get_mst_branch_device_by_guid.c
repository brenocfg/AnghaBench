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
typedef  int /*<<< orphan*/  uint8_t ;
struct drm_dp_mst_topology_mgr {int /*<<< orphan*/  lock; int /*<<< orphan*/  mst_primary; } ;
struct drm_dp_mst_branch {int dummy; } ;

/* Variables and functions */
 int drm_dp_mst_topology_try_get_mstb (struct drm_dp_mst_branch*) ; 
 struct drm_dp_mst_branch* get_mst_branch_device_by_guid_helper (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct drm_dp_mst_branch *
drm_dp_get_mst_branch_device_by_guid(struct drm_dp_mst_topology_mgr *mgr,
				     uint8_t *guid)
{
	struct drm_dp_mst_branch *mstb;
	int ret;

	/* find the port by iterating down */
	mutex_lock(&mgr->lock);

	mstb = get_mst_branch_device_by_guid_helper(mgr->mst_primary, guid);
	if (mstb) {
		ret = drm_dp_mst_topology_try_get_mstb(mstb);
		if (!ret)
			mstb = NULL;
	}

	mutex_unlock(&mgr->lock);
	return mstb;
}