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
struct pm860x_platform_data {int dummy; } ;
struct pm860x_chip {int /*<<< orphan*/  dev; int /*<<< orphan*/  irq_base; } ;
struct TYPE_6__ {struct TYPE_6__* resources; int /*<<< orphan*/  num_resources; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int mfd_add_devices (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* onkey_devs ; 
 TYPE_1__* onkey_resources ; 

__attribute__((used)) static void device_onkey_init(struct pm860x_chip *chip,
					struct pm860x_platform_data *pdata)
{
	int ret;

	onkey_devs[0].num_resources = ARRAY_SIZE(onkey_resources);
	onkey_devs[0].resources = &onkey_resources[0],
	ret = mfd_add_devices(chip->dev, 0, &onkey_devs[0],
			      ARRAY_SIZE(onkey_devs), &onkey_resources[0],
			      chip->irq_base, NULL);
	if (ret < 0)
		dev_err(chip->dev, "Failed to add onkey subdev\n");
}