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
typedef  int /*<<< orphan*/  u32 ;
struct rtc_time {int dummy; } ;
struct device {int dummy; } ;
struct cros_ec_rtc {struct cros_ec_device* cros_ec; } ;
struct cros_ec_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EC_CMD_RTC_GET_VALUE ; 
 int cros_ec_rtc_get (struct cros_ec_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 struct cros_ec_rtc* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  rtc_time64_to_tm (int /*<<< orphan*/ ,struct rtc_time*) ; 

__attribute__((used)) static int cros_ec_rtc_read_time(struct device *dev, struct rtc_time *tm)
{
	struct cros_ec_rtc *cros_ec_rtc = dev_get_drvdata(dev);
	struct cros_ec_device *cros_ec = cros_ec_rtc->cros_ec;
	int ret;
	u32 time;

	ret = cros_ec_rtc_get(cros_ec, EC_CMD_RTC_GET_VALUE, &time);
	if (ret) {
		dev_err(dev, "error getting time: %d\n", ret);
		return ret;
	}

	rtc_time64_to_tm(time, tm);

	return 0;
}