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
struct vf50_touch_device {TYPE_1__* pdev; int /*<<< orphan*/  gpio_ym; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  COLI_PULLUP_MAX_DELAY_US ; 
 int /*<<< orphan*/  COLI_PULLUP_MIN_DELAY_US ; 
 int /*<<< orphan*/  gpiod_set_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pinctrl_pm_select_idle_state (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usleep_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vf50_ts_enable_touch_detection(struct vf50_touch_device *vf50_ts)
{
	/* Enable plate YM (needs to be strong GND, high active) */
	gpiod_set_value(vf50_ts->gpio_ym, 1);

	/*
	 * Let the platform mux to idle state in order to enable
	 * Pull-Up on GPIO
	 */
	pinctrl_pm_select_idle_state(&vf50_ts->pdev->dev);

	/* Wait for the pull-up to be stable on high */
	usleep_range(COLI_PULLUP_MIN_DELAY_US, COLI_PULLUP_MAX_DELAY_US);
}