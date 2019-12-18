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
struct mdp4_lvds_connector {struct drm_panel* panel; } ;
struct drm_panel {TYPE_1__* funcs; } ;
struct drm_connector {int dummy; } ;
struct TYPE_2__ {int (* get_modes ) (struct drm_panel*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  drm_panel_attach (struct drm_panel*,struct drm_connector*) ; 
 int /*<<< orphan*/  drm_panel_detach (struct drm_panel*) ; 
 int stub1 (struct drm_panel*) ; 
 struct mdp4_lvds_connector* to_mdp4_lvds_connector (struct drm_connector*) ; 

__attribute__((used)) static int mdp4_lvds_connector_get_modes(struct drm_connector *connector)
{
	struct mdp4_lvds_connector *mdp4_lvds_connector =
			to_mdp4_lvds_connector(connector);
	struct drm_panel *panel = mdp4_lvds_connector->panel;
	int ret = 0;

	if (panel) {
		drm_panel_attach(panel, connector);

		ret = panel->funcs->get_modes(panel);

		drm_panel_detach(panel);
	}

	return ret;
}