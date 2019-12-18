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
struct drm_dp_mst_topology_mgr {int /*<<< orphan*/ * funcs; int /*<<< orphan*/  base; int /*<<< orphan*/ * aux; int /*<<< orphan*/ * dev; int /*<<< orphan*/  payload_lock; int /*<<< orphan*/ * proposed_vcpis; int /*<<< orphan*/ * payloads; int /*<<< orphan*/  destroy_connector_work; int /*<<< orphan*/  work; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_atomic_private_obj_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_dp_mst_topology_mgr_set_mst (struct drm_dp_mst_topology_mgr*,int) ; 
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void drm_dp_mst_topology_mgr_destroy(struct drm_dp_mst_topology_mgr *mgr)
{
	drm_dp_mst_topology_mgr_set_mst(mgr, false);
	flush_work(&mgr->work);
	flush_work(&mgr->destroy_connector_work);
	mutex_lock(&mgr->payload_lock);
	kfree(mgr->payloads);
	mgr->payloads = NULL;
	kfree(mgr->proposed_vcpis);
	mgr->proposed_vcpis = NULL;
	mutex_unlock(&mgr->payload_lock);
	mgr->dev = NULL;
	mgr->aux = NULL;
	drm_atomic_private_obj_fini(&mgr->base);
	mgr->funcs = NULL;
}