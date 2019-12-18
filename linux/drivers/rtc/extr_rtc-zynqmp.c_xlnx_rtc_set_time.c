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
struct xlnx_rtc_dev {unsigned long calibval; scalar_t__ reg_base; } ;
struct rtc_time {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 unsigned long RTC_CALIB_MASK ; 
 scalar_t__ RTC_CALIB_WR ; 
 unsigned long RTC_INT_SEC ; 
 scalar_t__ RTC_INT_STS ; 
 scalar_t__ RTC_SET_TM_WR ; 
 struct xlnx_rtc_dev* dev_get_drvdata (struct device*) ; 
 int rtc_tm_to_time64 (struct rtc_time*) ; 
 int /*<<< orphan*/  writel (unsigned long,scalar_t__) ; 

__attribute__((used)) static int xlnx_rtc_set_time(struct device *dev, struct rtc_time *tm)
{
	struct xlnx_rtc_dev *xrtcdev = dev_get_drvdata(dev);
	unsigned long new_time;

	/*
	 * The value written will be updated after 1 sec into the
	 * seconds read register, so we need to program time +1 sec
	 * to get the correct time on read.
	 */
	new_time = rtc_tm_to_time64(tm) + 1;

	/*
	 * Writing into calibration register will clear the Tick Counter and
	 * force the next second to be signaled exactly in 1 second period
	 */
	xrtcdev->calibval &= RTC_CALIB_MASK;
	writel(xrtcdev->calibval, (xrtcdev->reg_base + RTC_CALIB_WR));

	writel(new_time, xrtcdev->reg_base + RTC_SET_TM_WR);

	/*
	 * Clear the rtc interrupt status register after setting the
	 * time. During a read_time function, the code should read the
	 * RTC_INT_STATUS register and if bit 0 is still 0, it means
	 * that one second has not elapsed yet since RTC was set and
	 * the current time should be read from SET_TIME_READ register;
	 * otherwise, CURRENT_TIME register is read to report the time
	 */
	writel(RTC_INT_SEC, xrtcdev->reg_base + RTC_INT_STS);

	return 0;
}