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
struct lm3530_data {int enable; TYPE_1__ led_dev; int /*<<< orphan*/  regulator; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int regulator_enable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lm3530_led_enable(struct lm3530_data *drvdata)
{
	int ret;

	if (drvdata->enable)
		return 0;

	ret = regulator_enable(drvdata->regulator);
	if (ret) {
		dev_err(drvdata->led_dev.dev, "Failed to enable vin:%d\n", ret);
		return ret;
	}

	drvdata->enable = true;
	return 0;
}