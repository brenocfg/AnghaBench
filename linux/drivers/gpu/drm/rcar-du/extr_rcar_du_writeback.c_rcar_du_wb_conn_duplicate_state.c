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
struct rcar_du_wb_conn_state {struct drm_connector_state state; } ;
struct drm_connector {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  __drm_atomic_helper_connector_duplicate_state (struct drm_connector*,struct drm_connector_state*) ; 
 struct rcar_du_wb_conn_state* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct drm_connector_state *
rcar_du_wb_conn_duplicate_state(struct drm_connector *connector)
{
	struct rcar_du_wb_conn_state *copy;

	if (WARN_ON(!connector->state))
		return NULL;

	copy = kzalloc(sizeof(*copy), GFP_KERNEL);
	if (!copy)
		return NULL;

	__drm_atomic_helper_connector_duplicate_state(connector, &copy->state);

	return &copy->state;
}