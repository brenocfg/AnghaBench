#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct drm_dp_mst_topology_state {int dummy; } ;
struct drm_dp_mst_topology_mgr {int /*<<< orphan*/  base; struct drm_device* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  connection_mutex; } ;
struct drm_device {TYPE_1__ mode_config; } ;
struct drm_atomic_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  drm_atomic_get_private_obj_state (struct drm_atomic_state*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_modeset_is_locked (int /*<<< orphan*/ *) ; 
 struct drm_dp_mst_topology_state* to_dp_mst_topology_state (int /*<<< orphan*/ ) ; 

struct drm_dp_mst_topology_state *drm_atomic_get_mst_topology_state(struct drm_atomic_state *state,
								    struct drm_dp_mst_topology_mgr *mgr)
{
	struct drm_device *dev = mgr->dev;

	WARN_ON(!drm_modeset_is_locked(&dev->mode_config.connection_mutex));
	return to_dp_mst_topology_state(drm_atomic_get_private_obj_state(state, &mgr->base));
}