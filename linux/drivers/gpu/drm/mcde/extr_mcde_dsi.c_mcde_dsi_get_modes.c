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
struct mcde_dsi {scalar_t__ panel; } ;
struct drm_connector {int dummy; } ;

/* Variables and functions */
 struct mcde_dsi* connector_to_mcde_dsi (struct drm_connector*) ; 
 int drm_panel_get_modes (scalar_t__) ; 

__attribute__((used)) static int mcde_dsi_get_modes(struct drm_connector *connector)
{
	struct mcde_dsi *d = connector_to_mcde_dsi(connector);

	/* Just pass the question to the panel */
	if (d->panel)
		return drm_panel_get_modes(d->panel);

	/* TODO: deal with bridges */

	return 0;
}