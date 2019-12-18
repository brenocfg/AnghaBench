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
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct wm8350_led {int enabled; int /*<<< orphan*/  isink; TYPE_1__ cdev; int /*<<< orphan*/  dcdc; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 
 int regulator_enable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wm8350_led_enable(struct wm8350_led *led)
{
	int ret = 0;

	if (led->enabled)
		return ret;

	ret = regulator_enable(led->isink);
	if (ret != 0) {
		dev_err(led->cdev.dev, "Failed to enable ISINK: %d\n", ret);
		return ret;
	}

	ret = regulator_enable(led->dcdc);
	if (ret != 0) {
		dev_err(led->cdev.dev, "Failed to enable DCDC: %d\n", ret);
		regulator_disable(led->isink);
		return ret;
	}

	led->enabled = 1;

	return ret;
}