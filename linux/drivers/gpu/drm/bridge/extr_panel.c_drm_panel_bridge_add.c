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
typedef  int /*<<< orphan*/  u32 ;
struct drm_bridge {int /*<<< orphan*/  of_node; int /*<<< orphan*/ * funcs; } ;
struct panel_bridge {struct drm_bridge bridge; struct drm_panel* panel; int /*<<< orphan*/  connector_type; } ;
struct drm_panel {TYPE_1__* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct drm_bridge* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct panel_bridge* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_bridge_add (struct drm_bridge*) ; 
 int /*<<< orphan*/  panel_bridge_bridge_funcs ; 

struct drm_bridge *drm_panel_bridge_add(struct drm_panel *panel,
					u32 connector_type)
{
	struct panel_bridge *panel_bridge;

	if (!panel)
		return ERR_PTR(-EINVAL);

	panel_bridge = devm_kzalloc(panel->dev, sizeof(*panel_bridge),
				    GFP_KERNEL);
	if (!panel_bridge)
		return ERR_PTR(-ENOMEM);

	panel_bridge->connector_type = connector_type;
	panel_bridge->panel = panel;

	panel_bridge->bridge.funcs = &panel_bridge_bridge_funcs;
#ifdef CONFIG_OF
	panel_bridge->bridge.of_node = panel->dev->of_node;
#endif

	drm_bridge_add(&panel_bridge->bridge);

	return &panel_bridge->bridge;
}