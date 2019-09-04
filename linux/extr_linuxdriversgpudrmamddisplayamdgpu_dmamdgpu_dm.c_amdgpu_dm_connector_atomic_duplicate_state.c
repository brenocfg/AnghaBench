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
struct drm_connector_state {int dummy; } ;
struct drm_connector {int /*<<< orphan*/  state; } ;
struct dm_connector_state {struct drm_connector_state base; int /*<<< orphan*/  max_bpc; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  __drm_atomic_helper_connector_duplicate_state (struct drm_connector*,struct drm_connector_state*) ; 
 struct dm_connector_state* kmemdup (struct dm_connector_state*,int,int /*<<< orphan*/ ) ; 
 struct dm_connector_state* to_dm_connector_state (int /*<<< orphan*/ ) ; 

struct drm_connector_state *
amdgpu_dm_connector_atomic_duplicate_state(struct drm_connector *connector)
{
	struct dm_connector_state *state =
		to_dm_connector_state(connector->state);

	struct dm_connector_state *new_state =
			kmemdup(state, sizeof(*state), GFP_KERNEL);

	if (new_state) {
		__drm_atomic_helper_connector_duplicate_state(connector,
							      &new_state->base);
		new_state->max_bpc = state->max_bpc;
		return &new_state->base;
	}

	return NULL;
}