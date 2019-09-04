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
struct regulator_led {scalar_t__ enabled; TYPE_1__ cdev; int /*<<< orphan*/  vcc; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int regulator_disable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void regulator_led_disable(struct regulator_led *led)
{
	int ret;

	if (!led->enabled)
		return;

	ret = regulator_disable(led->vcc);
	if (ret != 0) {
		dev_err(led->cdev.dev, "Failed to disable vcc: %d\n", ret);
		return;
	}

	led->enabled = 0;
}