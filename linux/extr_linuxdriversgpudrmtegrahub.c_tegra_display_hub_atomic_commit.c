#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tegra_drm {struct tegra_display_hub* hub; } ;
struct tegra_display_hub_state {scalar_t__ dc; scalar_t__ clk; int /*<<< orphan*/  rate; } ;
struct TYPE_4__ {int /*<<< orphan*/  state; } ;
struct TYPE_3__ {struct device* dev; } ;
struct tegra_display_hub {int /*<<< orphan*/  clk_disp; TYPE_2__ base; TYPE_1__ client; } ;
struct drm_device {struct tegra_drm* dev_private; } ;
struct drm_atomic_state {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int clk_set_parent (int /*<<< orphan*/ ,scalar_t__) ; 
 int clk_set_rate (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int /*<<< orphan*/ ,scalar_t__,...) ; 
 int /*<<< orphan*/  tegra_display_hub_update (scalar_t__) ; 
 struct tegra_display_hub_state* to_tegra_display_hub_state (int /*<<< orphan*/ ) ; 

void tegra_display_hub_atomic_commit(struct drm_device *drm,
				     struct drm_atomic_state *state)
{
	struct tegra_drm *tegra = drm->dev_private;
	struct tegra_display_hub *hub = tegra->hub;
	struct tegra_display_hub_state *hub_state;
	struct device *dev = hub->client.dev;
	int err;

	hub_state = to_tegra_display_hub_state(hub->base.state);

	if (hub_state->clk) {
		err = clk_set_rate(hub_state->clk, hub_state->rate);
		if (err < 0)
			dev_err(dev, "failed to set rate of %pC to %lu Hz\n",
				hub_state->clk, hub_state->rate);

		err = clk_set_parent(hub->clk_disp, hub_state->clk);
		if (err < 0)
			dev_err(dev, "failed to set parent of %pC to %pC: %d\n",
				hub->clk_disp, hub_state->clk, err);
	}

	if (hub_state->dc)
		tegra_display_hub_update(hub_state->dc);
}