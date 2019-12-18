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
struct ptn3460_bridge {int enabled; int /*<<< orphan*/  panel; int /*<<< orphan*/  gpio_rst_n; int /*<<< orphan*/  gpio_pd_n; } ;
struct drm_bridge {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 
 struct ptn3460_bridge* bridge_to_ptn3460 (struct drm_bridge*) ; 
 scalar_t__ drm_panel_prepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiod_set_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int ptn3460_select_edid (struct ptn3460_bridge*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void ptn3460_pre_enable(struct drm_bridge *bridge)
{
	struct ptn3460_bridge *ptn_bridge = bridge_to_ptn3460(bridge);
	int ret;

	if (ptn_bridge->enabled)
		return;

	gpiod_set_value(ptn_bridge->gpio_pd_n, 1);

	gpiod_set_value(ptn_bridge->gpio_rst_n, 0);
	usleep_range(10, 20);
	gpiod_set_value(ptn_bridge->gpio_rst_n, 1);

	if (drm_panel_prepare(ptn_bridge->panel)) {
		DRM_ERROR("failed to prepare panel\n");
		return;
	}

	/*
	 * There's a bug in the PTN chip where it falsely asserts hotplug before
	 * it is fully functional. We're forced to wait for the maximum start up
	 * time specified in the chip's datasheet to make sure we're really up.
	 */
	msleep(90);

	ret = ptn3460_select_edid(ptn_bridge);
	if (ret)
		DRM_ERROR("Select EDID failed ret=%d\n", ret);

	ptn_bridge->enabled = true;
}