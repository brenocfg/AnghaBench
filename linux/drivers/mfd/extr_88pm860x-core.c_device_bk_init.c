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
struct pm860x_platform_data {int num_backlights; int /*<<< orphan*/ * backlight; } ;
struct pm860x_chip {int /*<<< orphan*/  dev; } ;
struct pm860x_backlight_pdata {int dummy; } ;
struct TYPE_4__ {int pdata_size; int /*<<< orphan*/ * platform_data; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 TYPE_1__* bk_devs ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int mfd_add_devices (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void device_bk_init(struct pm860x_chip *chip,
				     struct pm860x_platform_data *pdata)
{
	int ret, i;

	if (pdata && pdata->backlight) {
		if (pdata->num_backlights > ARRAY_SIZE(bk_devs))
			pdata->num_backlights = ARRAY_SIZE(bk_devs);
		for (i = 0; i < pdata->num_backlights; i++) {
			bk_devs[i].platform_data = &pdata->backlight[i];
			bk_devs[i].pdata_size =
				sizeof(struct pm860x_backlight_pdata);
		}
	}
	ret = mfd_add_devices(chip->dev, 0, bk_devs,
			      ARRAY_SIZE(bk_devs), NULL, 0, NULL);
	if (ret < 0)
		dev_err(chip->dev, "Failed to add backlight subdev\n");
}