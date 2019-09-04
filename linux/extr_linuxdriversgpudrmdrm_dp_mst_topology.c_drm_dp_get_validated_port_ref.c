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
struct drm_dp_mst_topology_mgr {int /*<<< orphan*/  lock; scalar_t__ mst_primary; } ;
struct drm_dp_mst_port {int dummy; } ;

/* Variables and functions */
 struct drm_dp_mst_port* drm_dp_mst_get_port_ref_locked (scalar_t__,struct drm_dp_mst_port*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct drm_dp_mst_port *drm_dp_get_validated_port_ref(struct drm_dp_mst_topology_mgr *mgr, struct drm_dp_mst_port *port)
{
	struct drm_dp_mst_port *rport = NULL;
	mutex_lock(&mgr->lock);
	if (mgr->mst_primary)
		rport = drm_dp_mst_get_port_ref_locked(mgr->mst_primary, port);
	mutex_unlock(&mgr->lock);
	return rport;
}