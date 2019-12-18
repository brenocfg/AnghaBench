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
struct stmp3xxx_rtc_data {scalar_t__ io; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ STMP3XXX_RTC_CTRL ; 
 int /*<<< orphan*/  STMP3XXX_RTC_CTRL_ALARM_IRQ_EN ; 
 scalar_t__ STMP_OFFSET_REG_CLR ; 
 struct stmp3xxx_rtc_data* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int stmp3xxx_rtc_remove(struct platform_device *pdev)
{
	struct stmp3xxx_rtc_data *rtc_data = platform_get_drvdata(pdev);

	if (!rtc_data)
		return 0;

	writel(STMP3XXX_RTC_CTRL_ALARM_IRQ_EN,
		rtc_data->io + STMP3XXX_RTC_CTRL + STMP_OFFSET_REG_CLR);

	return 0;
}