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
struct drm_dp_mst_port {struct drm_dp_mst_branch* parent; struct drm_dp_mst_branch* mstb; } ;
struct drm_dp_mst_branch {struct drm_dp_mst_port* port_parent; } ;

/* Variables and functions */

__attribute__((used)) static struct drm_dp_mst_port *drm_dp_get_last_connected_port_to_mstb(struct drm_dp_mst_branch *mstb)
{
	if (!mstb->port_parent)
		return NULL;

	if (mstb->port_parent->mstb != mstb)
		return mstb->port_parent;

	return drm_dp_get_last_connected_port_to_mstb(mstb->port_parent->parent);
}