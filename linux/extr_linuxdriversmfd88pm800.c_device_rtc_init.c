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
struct pm80x_rtc_pdata {int dummy; } ;
struct pm80x_platform_data {scalar_t__ rtc; } ;
struct pm80x_chip {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int pdata_size; scalar_t__ platform_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int mfd_add_devices (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* rtc_devs ; 

__attribute__((used)) static int device_rtc_init(struct pm80x_chip *chip,
				struct pm80x_platform_data *pdata)
{
	int ret;

	if (pdata) {
		rtc_devs[0].platform_data = pdata->rtc;
		rtc_devs[0].pdata_size =
				pdata->rtc ? sizeof(struct pm80x_rtc_pdata) : 0;
	}
	ret = mfd_add_devices(chip->dev, 0, &rtc_devs[0],
			      ARRAY_SIZE(rtc_devs), NULL, 0, NULL);
	if (ret) {
		dev_err(chip->dev, "Failed to add rtc subdev\n");
		return ret;
	}

	return 0;
}