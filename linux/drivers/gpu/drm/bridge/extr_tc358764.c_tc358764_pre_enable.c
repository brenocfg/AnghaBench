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
struct tc358764 {int /*<<< orphan*/  dev; int /*<<< orphan*/  panel; int /*<<< orphan*/  supplies; } ;
struct drm_bridge {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 struct tc358764* bridge_to_tc358764 (struct drm_bridge*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int drm_panel_prepare (int /*<<< orphan*/ ) ; 
 int regulator_bulk_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int tc358764_init (struct tc358764*) ; 
 int /*<<< orphan*/  tc358764_reset (struct tc358764*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void tc358764_pre_enable(struct drm_bridge *bridge)
{
	struct tc358764 *ctx = bridge_to_tc358764(bridge);
	int ret;

	ret = regulator_bulk_enable(ARRAY_SIZE(ctx->supplies), ctx->supplies);
	if (ret < 0)
		dev_err(ctx->dev, "error enabling regulators (%d)\n", ret);
	usleep_range(10000, 15000);
	tc358764_reset(ctx);
	ret = tc358764_init(ctx);
	if (ret < 0)
		dev_err(ctx->dev, "error initializing bridge (%d)\n", ret);
	ret = drm_panel_prepare(ctx->panel);
	if (ret < 0)
		dev_err(ctx->dev, "error preparing panel (%d)\n", ret);
}