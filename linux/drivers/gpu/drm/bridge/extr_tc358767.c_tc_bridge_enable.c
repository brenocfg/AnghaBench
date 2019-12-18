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
struct tc_data {int /*<<< orphan*/  panel; int /*<<< orphan*/  dev; } ;
struct drm_bridge {int dummy; } ;

/* Variables and functions */
 struct tc_data* bridge_to_tc (struct drm_bridge*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  drm_panel_enable (int /*<<< orphan*/ ) ; 
 int tc_get_display_props (struct tc_data*) ; 
 int /*<<< orphan*/  tc_main_link_disable (struct tc_data*) ; 
 int tc_main_link_enable (struct tc_data*) ; 
 int tc_stream_enable (struct tc_data*) ; 

__attribute__((used)) static void tc_bridge_enable(struct drm_bridge *bridge)
{
	struct tc_data *tc = bridge_to_tc(bridge);
	int ret;

	ret = tc_get_display_props(tc);
	if (ret < 0) {
		dev_err(tc->dev, "failed to read display props: %d\n", ret);
		return;
	}

	ret = tc_main_link_enable(tc);
	if (ret < 0) {
		dev_err(tc->dev, "main link enable error: %d\n", ret);
		return;
	}

	ret = tc_stream_enable(tc);
	if (ret < 0) {
		dev_err(tc->dev, "main link stream start error: %d\n", ret);
		tc_main_link_disable(tc);
		return;
	}

	drm_panel_enable(tc->panel);
}