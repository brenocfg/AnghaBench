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
struct tc358764 {int /*<<< orphan*/  dev; int /*<<< orphan*/  panel; } ;
struct drm_bridge {int dummy; } ;

/* Variables and functions */
 struct tc358764* bridge_to_tc358764 (struct drm_bridge*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int drm_panel_disable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tc358764_disable(struct drm_bridge *bridge)
{
	struct tc358764 *ctx = bridge_to_tc358764(bridge);
	int ret = drm_panel_disable(bridge_to_tc358764(bridge)->panel);

	if (ret < 0)
		dev_err(ctx->dev, "error disabling panel (%d)\n", ret);
}