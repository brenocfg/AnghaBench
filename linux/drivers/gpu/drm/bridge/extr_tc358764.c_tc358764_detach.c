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
struct tc358764 {int /*<<< orphan*/  connector; int /*<<< orphan*/ * panel; } ;
struct drm_device {int /*<<< orphan*/  fb_helper; } ;
struct drm_bridge {struct drm_device* dev; } ;

/* Variables and functions */
 struct tc358764* bridge_to_tc358764 (struct drm_bridge*) ; 
 int /*<<< orphan*/  drm_connector_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_connector_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_fb_helper_remove_one_connector (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_panel_detach (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void tc358764_detach(struct drm_bridge *bridge)
{
	struct tc358764 *ctx = bridge_to_tc358764(bridge);
	struct drm_device *drm = bridge->dev;

	drm_connector_unregister(&ctx->connector);
	drm_fb_helper_remove_one_connector(drm->fb_helper, &ctx->connector);
	drm_panel_detach(ctx->panel);
	ctx->panel = NULL;
	drm_connector_put(&ctx->connector);
}