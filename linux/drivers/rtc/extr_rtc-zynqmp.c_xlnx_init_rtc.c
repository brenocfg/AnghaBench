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
struct xlnx_rtc_dev {scalar_t__ reg_base; int /*<<< orphan*/  calibval; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTC_BATT_EN ; 
 int /*<<< orphan*/  RTC_CALIB_MASK ; 
 scalar_t__ RTC_CALIB_WR ; 
 scalar_t__ RTC_CTRL ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void xlnx_init_rtc(struct xlnx_rtc_dev *xrtcdev)
{
	u32 rtc_ctrl;

	/* Enable RTC switch to battery when VCC_PSAUX is not available */
	rtc_ctrl = readl(xrtcdev->reg_base + RTC_CTRL);
	rtc_ctrl |= RTC_BATT_EN;
	writel(rtc_ctrl, xrtcdev->reg_base + RTC_CTRL);

	/*
	 * Based on crystal freq of 33.330 KHz
	 * set the seconds counter and enable, set fractions counter
	 * to default value suggested as per design spec
	 * to correct RTC delay in frequency over period of time.
	 */
	xrtcdev->calibval &= RTC_CALIB_MASK;
	writel(xrtcdev->calibval, (xrtcdev->reg_base + RTC_CALIB_WR));
}