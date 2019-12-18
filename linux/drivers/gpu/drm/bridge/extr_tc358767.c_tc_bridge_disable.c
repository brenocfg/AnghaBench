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
struct tc_data {int /*<<< orphan*/  dev; int /*<<< orphan*/  panel; } ;
struct drm_bridge {int dummy; } ;

/* Variables and functions */
 struct tc_data* bridge_to_tc (struct drm_bridge*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  drm_panel_disable (int /*<<< orphan*/ ) ; 
 int tc_main_link_disable (struct tc_data*) ; 
 int tc_stream_disable (struct tc_data*) ; 

__attribute__((used)) static void tc_bridge_disable(struct drm_bridge *bridge)
{
	struct tc_data *tc = bridge_to_tc(bridge);
	int ret;

	drm_panel_disable(tc->panel);

	ret = tc_stream_disable(tc);
	if (ret < 0)
		dev_err(tc->dev, "main link stream stop error: %d\n", ret);

	ret = tc_main_link_disable(tc);
	if (ret < 0)
		dev_err(tc->dev, "main link disable error: %d\n", ret);
}