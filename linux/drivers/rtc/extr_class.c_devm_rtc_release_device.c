#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct rtc_device {int /*<<< orphan*/  dev; scalar_t__ registered; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtc_device_unregister (struct rtc_device*) ; 
 int /*<<< orphan*/  rtc_nvmem_unregister (struct rtc_device*) ; 

__attribute__((used)) static void devm_rtc_release_device(struct device *dev, void *res)
{
	struct rtc_device *rtc = *(struct rtc_device **)res;

	rtc_nvmem_unregister(rtc);

	if (rtc->registered)
		rtc_device_unregister(rtc);
	else
		put_device(&rtc->dev);
}