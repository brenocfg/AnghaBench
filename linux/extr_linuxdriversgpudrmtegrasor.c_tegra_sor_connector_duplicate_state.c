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
struct tegra_sor_state {struct drm_connector_state base; } ;
struct drm_connector {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  __drm_atomic_helper_connector_duplicate_state (struct drm_connector*,struct drm_connector_state*) ; 
 struct tegra_sor_state* kmemdup (struct tegra_sor_state*,int,int /*<<< orphan*/ ) ; 
 struct tegra_sor_state* to_sor_state (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct drm_connector_state *
tegra_sor_connector_duplicate_state(struct drm_connector *connector)
{
	struct tegra_sor_state *state = to_sor_state(connector->state);
	struct tegra_sor_state *copy;

	copy = kmemdup(state, sizeof(*state), GFP_KERNEL);
	if (!copy)
		return NULL;

	__drm_atomic_helper_connector_duplicate_state(connector, &copy->base);

	return &copy->base;
}