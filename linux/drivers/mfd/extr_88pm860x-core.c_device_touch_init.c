#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct pm860x_touch_pdata {int dummy; } ;
struct pm860x_platform_data {int /*<<< orphan*/  touch; } ;
struct pm860x_chip {int /*<<< orphan*/  dev; int /*<<< orphan*/  irq_base; } ;
struct TYPE_6__ {int pdata_size; struct TYPE_6__* resources; int /*<<< orphan*/  num_resources; int /*<<< orphan*/  platform_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int mfd_add_devices (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* touch_devs ; 
 TYPE_1__* touch_resources ; 

__attribute__((used)) static void device_touch_init(struct pm860x_chip *chip,
					struct pm860x_platform_data *pdata)
{
	int ret;

	if (pdata == NULL)
		return;

	touch_devs[0].platform_data = pdata->touch;
	touch_devs[0].pdata_size = sizeof(struct pm860x_touch_pdata);
	touch_devs[0].num_resources = ARRAY_SIZE(touch_resources);
	touch_devs[0].resources = &touch_resources[0];
	ret = mfd_add_devices(chip->dev, 0, &touch_devs[0],
			      ARRAY_SIZE(touch_devs), &touch_resources[0],
			      chip->irq_base, NULL);
	if (ret < 0)
		dev_err(chip->dev, "Failed to add touch subdev\n");
}