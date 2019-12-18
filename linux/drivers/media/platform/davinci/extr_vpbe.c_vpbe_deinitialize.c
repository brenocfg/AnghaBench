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
struct vpbe_device {scalar_t__ initialized; int /*<<< orphan*/  encoders; int /*<<< orphan*/  amp; int /*<<< orphan*/  dac_clk; TYPE_1__* cfg; int /*<<< orphan*/  v4l2_dev; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  module_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  VPSS_VPBE_CLOCK ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  v4l2_device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vpss_enable_clock (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vpbe_deinitialize(struct device *dev, struct vpbe_device *vpbe_dev)
{
	v4l2_device_unregister(&vpbe_dev->v4l2_dev);
	if (strcmp(vpbe_dev->cfg->module_name, "dm644x-vpbe-display") != 0) {
		clk_disable_unprepare(vpbe_dev->dac_clk);
		clk_put(vpbe_dev->dac_clk);
	}

	kfree(vpbe_dev->amp);
	kfree(vpbe_dev->encoders);
	vpbe_dev->initialized = 0;
	/* disable vpss clocks */
	vpss_enable_clock(VPSS_VPBE_CLOCK, 0);
}