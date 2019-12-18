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
struct xlnx_rtc_dev {scalar_t__ reg_base; } ;
struct rtc_time {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ RTC_CUR_TM ; 
 int RTC_INT_SEC ; 
 scalar_t__ RTC_INT_STS ; 
 scalar_t__ RTC_SET_TM_RD ; 
 struct xlnx_rtc_dev* dev_get_drvdata (struct device*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  rtc_time64_to_tm (unsigned long,struct rtc_time*) ; 

__attribute__((used)) static int xlnx_rtc_read_time(struct device *dev, struct rtc_time *tm)
{
	u32 status;
	unsigned long read_time;
	struct xlnx_rtc_dev *xrtcdev = dev_get_drvdata(dev);

	status = readl(xrtcdev->reg_base + RTC_INT_STS);

	if (status & RTC_INT_SEC) {
		/*
		 * RTC has updated the CURRENT_TIME with the time written into
		 * SET_TIME_WRITE register.
		 */
		rtc_time64_to_tm(readl(xrtcdev->reg_base + RTC_CUR_TM), tm);
	} else {
		/*
		 * Time written in SET_TIME_WRITE has not yet updated into
		 * the seconds read register, so read the time from the
		 * SET_TIME_WRITE instead of CURRENT_TIME register.
		 * Since we add +1 sec while writing, we need to -1 sec while
		 * reading.
		 */
		read_time = readl(xrtcdev->reg_base + RTC_SET_TM_RD) - 1;
		rtc_time64_to_tm(read_time, tm);
	}

	return 0;
}