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
struct TYPE_2__ {int /*<<< orphan*/  panel; struct drm_connector* edid; } ;
struct intel_lvds_connector {TYPE_1__ base; } ;
struct drm_connector {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR_OR_NULL (struct drm_connector*) ; 
 int /*<<< orphan*/  drm_connector_cleanup (struct drm_connector*) ; 
 int /*<<< orphan*/  intel_panel_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct drm_connector*) ; 
 struct intel_lvds_connector* to_lvds_connector (struct drm_connector*) ; 

__attribute__((used)) static void intel_lvds_destroy(struct drm_connector *connector)
{
	struct intel_lvds_connector *lvds_connector =
		to_lvds_connector(connector);

	if (!IS_ERR_OR_NULL(lvds_connector->base.edid))
		kfree(lvds_connector->base.edid);

	intel_panel_fini(&lvds_connector->base.panel);

	drm_connector_cleanup(connector);
	kfree(connector);
}