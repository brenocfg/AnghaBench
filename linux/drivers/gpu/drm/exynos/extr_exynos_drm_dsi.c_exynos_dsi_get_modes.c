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
struct exynos_dsi {TYPE_2__* panel; } ;
struct drm_connector {int dummy; } ;
struct TYPE_4__ {TYPE_1__* funcs; } ;
struct TYPE_3__ {int (* get_modes ) (TYPE_2__*) ;} ;

/* Variables and functions */
 struct exynos_dsi* connector_to_dsi (struct drm_connector*) ; 
 int stub1 (TYPE_2__*) ; 

__attribute__((used)) static int exynos_dsi_get_modes(struct drm_connector *connector)
{
	struct exynos_dsi *dsi = connector_to_dsi(connector);

	if (dsi->panel)
		return dsi->panel->funcs->get_modes(dsi->panel);

	return 0;
}