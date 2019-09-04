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
struct tegra_display_hub_state {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;
struct tegra_display_hub {int /*<<< orphan*/  base; TYPE_1__ client; } ;
struct drm_private_state {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  connection_mutex; } ;
struct drm_device {TYPE_2__ mode_config; } ;
struct drm_atomic_state {int dummy; } ;

/* Variables and functions */
 struct tegra_display_hub_state* ERR_CAST (struct drm_private_state*) ; 
 scalar_t__ IS_ERR (struct drm_private_state*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct drm_device* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 struct drm_private_state* drm_atomic_get_private_obj_state (struct drm_atomic_state*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_modeset_is_locked (int /*<<< orphan*/ *) ; 
 struct tegra_display_hub_state* to_tegra_display_hub_state (struct drm_private_state*) ; 

__attribute__((used)) static struct tegra_display_hub_state *
tegra_display_hub_get_state(struct tegra_display_hub *hub,
			    struct drm_atomic_state *state)
{
	struct drm_device *drm = dev_get_drvdata(hub->client.parent);
	struct drm_private_state *priv;

	WARN_ON(!drm_modeset_is_locked(&drm->mode_config.connection_mutex));

	priv = drm_atomic_get_private_obj_state(state, &hub->base);
	if (IS_ERR(priv))
		return ERR_CAST(priv);

	return to_tegra_display_hub_state(priv);
}