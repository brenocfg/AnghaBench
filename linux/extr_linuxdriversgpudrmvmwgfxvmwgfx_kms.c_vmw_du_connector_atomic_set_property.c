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
typedef  int /*<<< orphan*/  uint64_t ;
struct vmw_private {struct drm_property* implicit_placement_property; } ;
struct vmw_display_unit {int /*<<< orphan*/  is_implicit; } ;
struct vmw_connector_state {int /*<<< orphan*/  is_implicit; } ;
struct drm_property {int dummy; } ;
struct drm_connector_state {int dummy; } ;
struct drm_connector {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 struct vmw_connector_state* vmw_connector_state_to_vcs (struct drm_connector_state*) ; 
 struct vmw_display_unit* vmw_connector_to_du (struct drm_connector*) ; 
 struct vmw_private* vmw_priv (int /*<<< orphan*/ ) ; 

int
vmw_du_connector_atomic_set_property(struct drm_connector *connector,
				     struct drm_connector_state *state,
				     struct drm_property *property,
				     uint64_t val)
{
	struct vmw_private *dev_priv = vmw_priv(connector->dev);
	struct vmw_connector_state *vcs = vmw_connector_state_to_vcs(state);
	struct vmw_display_unit *du = vmw_connector_to_du(connector);


	if (property == dev_priv->implicit_placement_property) {
		vcs->is_implicit = val;

		/*
		 * We should really be doing a drm_atomic_commit() to
		 * commit the new state, but since this doesn't cause
		 * an immedate state change, this is probably ok
		 */
		du->is_implicit = vcs->is_implicit;
	} else {
		return -EINVAL;
	}

	return 0;
}