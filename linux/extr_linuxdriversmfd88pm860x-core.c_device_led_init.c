#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pm860x_platform_data {int num_leds; int /*<<< orphan*/ * led; } ;
struct pm860x_led_pdata {int dummy; } ;
struct pm860x_chip {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int pdata_size; int /*<<< orphan*/ * platform_data; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* led_devs ; 
 int mfd_add_devices (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void device_led_init(struct pm860x_chip *chip,
				      struct pm860x_platform_data *pdata)
{
	int ret, i;

	if (pdata && pdata->led) {
		if (pdata->num_leds > ARRAY_SIZE(led_devs))
			pdata->num_leds = ARRAY_SIZE(led_devs);
		for (i = 0; i < pdata->num_leds; i++) {
			led_devs[i].platform_data = &pdata->led[i];
			led_devs[i].pdata_size =
				sizeof(struct pm860x_led_pdata);
		}
	}
	ret = mfd_add_devices(chip->dev, 0, led_devs,
			      ARRAY_SIZE(led_devs), NULL, 0, NULL);
	if (ret < 0) {
		dev_err(chip->dev, "Failed to add led subdev\n");
		return;
	}
}