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
struct rtc_device {int /*<<< orphan*/  range_max; int /*<<< orphan*/  range_min; int /*<<< orphan*/ * ops; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int ETIMEDOUT ; 
 scalar_t__ IS_ERR (struct rtc_device*) ; 
 int PTR_ERR (struct rtc_device*) ; 
 unsigned long RTC_CNTR_OK ; 
 int /*<<< orphan*/  RTC_TIMESTAMP_BEGIN_1900 ; 
 int /*<<< orphan*/  RTC_TIMESTAMP_END_2099 ; 
 int SYS_CNTRL_TTS ; 
 int /*<<< orphan*/  SYS_COUNTER_CNTRL ; 
 int /*<<< orphan*/  SYS_TOYTRIM ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct rtc_device* devm_rtc_allocate_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ls1x_rtc_ops ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct rtc_device*) ; 
 int readl (int /*<<< orphan*/ ) ; 
 int rtc_register_device (struct rtc_device*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ls1x_rtc_probe(struct platform_device *pdev)
{
	struct rtc_device *rtcdev;
	unsigned long v;

	v = readl(SYS_COUNTER_CNTRL);
	if (!(v & RTC_CNTR_OK)) {
		dev_err(&pdev->dev, "rtc counters not working\n");
		return -ENODEV;
	}

	/* set to 1 HZ if needed */
	if (readl(SYS_TOYTRIM) != 32767) {
		v = 0x100000;
		while ((readl(SYS_COUNTER_CNTRL) & SYS_CNTRL_TTS) && --v)
			usleep_range(1000, 3000);

		if (!v) {
			dev_err(&pdev->dev, "time out\n");
			return -ETIMEDOUT;
		}
		writel(32767, SYS_TOYTRIM);
	}
	/* this loop coundn't be endless */
	while (readl(SYS_COUNTER_CNTRL) & SYS_CNTRL_TTS)
		usleep_range(1000, 3000);

	rtcdev = devm_rtc_allocate_device(&pdev->dev);
	if (IS_ERR(rtcdev))
		return PTR_ERR(rtcdev);

	platform_set_drvdata(pdev, rtcdev);
	rtcdev->ops = &ls1x_rtc_ops;
	rtcdev->range_min = RTC_TIMESTAMP_BEGIN_1900;
	rtcdev->range_max = RTC_TIMESTAMP_END_2099;

	return rtc_register_device(rtcdev);
}