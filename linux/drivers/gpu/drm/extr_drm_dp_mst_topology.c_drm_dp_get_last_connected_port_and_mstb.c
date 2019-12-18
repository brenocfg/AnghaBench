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
struct drm_dp_mst_topology_mgr {int /*<<< orphan*/  lock; int /*<<< orphan*/  mst_primary; } ;
struct drm_dp_mst_port {int port_num; struct drm_dp_mst_branch* parent; } ;
struct drm_dp_mst_branch {int dummy; } ;

/* Variables and functions */
 struct drm_dp_mst_port* drm_dp_get_last_connected_port_to_mstb (struct drm_dp_mst_branch*) ; 
 scalar_t__ drm_dp_mst_topology_try_get_mstb (struct drm_dp_mst_branch*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct drm_dp_mst_branch *
drm_dp_get_last_connected_port_and_mstb(struct drm_dp_mst_topology_mgr *mgr,
					struct drm_dp_mst_branch *mstb,
					int *port_num)
{
	struct drm_dp_mst_branch *rmstb = NULL;
	struct drm_dp_mst_port *found_port;

	mutex_lock(&mgr->lock);
	if (!mgr->mst_primary)
		goto out;

	do {
		found_port = drm_dp_get_last_connected_port_to_mstb(mstb);
		if (!found_port)
			break;

		if (drm_dp_mst_topology_try_get_mstb(found_port->parent)) {
			rmstb = found_port->parent;
			*port_num = found_port->port_num;
		} else {
			/* Search again, starting from this parent */
			mstb = found_port->parent;
		}
	} while (!rmstb);
out:
	mutex_unlock(&mgr->lock);
	return rmstb;
}