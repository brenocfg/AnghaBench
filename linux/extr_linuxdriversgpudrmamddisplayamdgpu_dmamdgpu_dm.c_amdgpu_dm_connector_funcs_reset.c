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
struct drm_connector {scalar_t__ state; } ;
struct dm_connector_state {int underscan_enable; int max_bpc; int /*<<< orphan*/  base; scalar_t__ underscan_vborder; scalar_t__ underscan_hborder; int /*<<< orphan*/  scaling; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  RMX_OFF ; 
 int /*<<< orphan*/  __drm_atomic_helper_connector_destroy_state (scalar_t__) ; 
 int /*<<< orphan*/  __drm_atomic_helper_connector_reset (struct drm_connector*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct dm_connector_state*) ; 
 struct dm_connector_state* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct dm_connector_state* to_dm_connector_state (scalar_t__) ; 

void amdgpu_dm_connector_funcs_reset(struct drm_connector *connector)
{
	struct dm_connector_state *state =
		to_dm_connector_state(connector->state);

	if (connector->state)
		__drm_atomic_helper_connector_destroy_state(connector->state);

	kfree(state);

	state = kzalloc(sizeof(*state), GFP_KERNEL);

	if (state) {
		state->scaling = RMX_OFF;
		state->underscan_enable = false;
		state->underscan_hborder = 0;
		state->underscan_vborder = 0;
		state->max_bpc = 8;

		__drm_atomic_helper_connector_reset(connector, &state->base);
	}
}