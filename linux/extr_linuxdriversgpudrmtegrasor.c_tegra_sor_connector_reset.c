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
struct tegra_sor_state {int /*<<< orphan*/  base; } ;
struct drm_connector {scalar_t__ state; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  __drm_atomic_helper_connector_destroy_state (scalar_t__) ; 
 int /*<<< orphan*/  __drm_atomic_helper_connector_reset (struct drm_connector*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (scalar_t__) ; 
 struct tegra_sor_state* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tegra_sor_connector_reset(struct drm_connector *connector)
{
	struct tegra_sor_state *state;

	state = kzalloc(sizeof(*state), GFP_KERNEL);
	if (!state)
		return;

	if (connector->state) {
		__drm_atomic_helper_connector_destroy_state(connector->state);
		kfree(connector->state);
	}

	__drm_atomic_helper_connector_reset(connector, &state->base);
}