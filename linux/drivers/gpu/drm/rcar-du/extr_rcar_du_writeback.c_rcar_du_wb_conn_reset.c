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
struct rcar_du_wb_conn_state {int /*<<< orphan*/  state; } ;
struct drm_connector {int /*<<< orphan*/ * state; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  __drm_atomic_helper_connector_reset (struct drm_connector*,int /*<<< orphan*/ *) ; 
 struct rcar_du_wb_conn_state* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcar_du_wb_conn_destroy_state (struct drm_connector*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rcar_du_wb_conn_reset(struct drm_connector *connector)
{
	struct rcar_du_wb_conn_state *state;

	if (connector->state) {
		rcar_du_wb_conn_destroy_state(connector, connector->state);
		connector->state = NULL;
	}

	state = kzalloc(sizeof(*state), GFP_KERNEL);
	if (state == NULL)
		return;

	__drm_atomic_helper_connector_reset(connector, &state->state);
}