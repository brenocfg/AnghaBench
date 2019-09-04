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
struct drm_dp_mst_topology_mgr {int /*<<< orphan*/  destroy_connector_work; int /*<<< orphan*/  work; int /*<<< orphan*/  lock; int /*<<< orphan*/  aux; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_MSTM_CTRL ; 
 int DP_MST_EN ; 
 int DP_UPSTREAM_IS_SRC ; 
 int /*<<< orphan*/  drm_dp_dpcd_writeb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void drm_dp_mst_topology_mgr_suspend(struct drm_dp_mst_topology_mgr *mgr)
{
	mutex_lock(&mgr->lock);
	drm_dp_dpcd_writeb(mgr->aux, DP_MSTM_CTRL,
			   DP_MST_EN | DP_UPSTREAM_IS_SRC);
	mutex_unlock(&mgr->lock);
	flush_work(&mgr->work);
	flush_work(&mgr->destroy_connector_work);
}