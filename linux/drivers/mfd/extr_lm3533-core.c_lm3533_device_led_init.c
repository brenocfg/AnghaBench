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
struct lm3533_platform_data {int num_leds; int /*<<< orphan*/ * leds; } ;
struct lm3533 {int have_leds; int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int pdata_size; int /*<<< orphan*/ * platform_data; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct lm3533_platform_data* dev_get_platdata (int /*<<< orphan*/ ) ; 
 TYPE_1__* lm3533_led_devs ; 
 int mfd_add_devices (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lm3533_device_led_init(struct lm3533 *lm3533)
{
	struct lm3533_platform_data *pdata = dev_get_platdata(lm3533->dev);
	int i;
	int ret;

	if (!pdata->leds || pdata->num_leds == 0)
		return 0;

	if (pdata->num_leds > ARRAY_SIZE(lm3533_led_devs))
		pdata->num_leds = ARRAY_SIZE(lm3533_led_devs);

	for (i = 0; i < pdata->num_leds; ++i) {
		lm3533_led_devs[i].platform_data = &pdata->leds[i];
		lm3533_led_devs[i].pdata_size = sizeof(pdata->leds[i]);
	}

	ret = mfd_add_devices(lm3533->dev, 0, lm3533_led_devs,
			      pdata->num_leds, NULL, 0, NULL);
	if (ret) {
		dev_err(lm3533->dev, "failed to add LED devices\n");
		return ret;
	}

	lm3533->have_leds = 1;

	return 0;
}