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
typedef  int u32 ;
typedef  int u16 ;
typedef  int /*<<< orphan*/  time1 ;
struct wm831x_rtc {struct wm831x* wm831x; } ;
struct wm831x {int dummy; } ;
struct rtc_time {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int WM831X_GET_TIME_RETRIES ; 
 int /*<<< orphan*/  WM831X_RTC_CONTROL ; 
 int /*<<< orphan*/  WM831X_RTC_TIME_1 ; 
 int WM831X_RTC_VALID ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 struct wm831x_rtc* dev_get_drvdata (struct device*) ; 
 scalar_t__ memcmp (int*,int*,int) ; 
 int /*<<< orphan*/  rtc_time64_to_tm (int,struct rtc_time*) ; 
 int wm831x_bulk_read (struct wm831x*,int /*<<< orphan*/ ,int,int*) ; 
 int wm831x_reg_read (struct wm831x*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wm831x_rtc_readtime(struct device *dev, struct rtc_time *tm)
{
	struct wm831x_rtc *wm831x_rtc = dev_get_drvdata(dev);
	struct wm831x *wm831x = wm831x_rtc->wm831x;
	u16 time1[2], time2[2];
	int ret;
	int count = 0;

	/* Has the RTC been programmed? */
	ret = wm831x_reg_read(wm831x, WM831X_RTC_CONTROL);
	if (ret < 0) {
		dev_err(dev, "Failed to read RTC control: %d\n", ret);
		return ret;
	}
	if (!(ret & WM831X_RTC_VALID)) {
		dev_dbg(dev, "RTC not yet configured\n");
		return -EINVAL;
	}

	/* Read twice to make sure we don't read a corrupt, partially
	 * incremented, value.
	 */
	do {
		ret = wm831x_bulk_read(wm831x, WM831X_RTC_TIME_1,
				       2, time1);
		if (ret != 0)
			continue;

		ret = wm831x_bulk_read(wm831x, WM831X_RTC_TIME_1,
				       2, time2);
		if (ret != 0)
			continue;

		if (memcmp(time1, time2, sizeof(time1)) == 0) {
			u32 time = (time1[0] << 16) | time1[1];

			rtc_time64_to_tm(time, tm);
			return 0;
		}

	} while (++count < WM831X_GET_TIME_RETRIES);

	dev_err(dev, "Timed out reading current time\n");

	return -EIO;
}