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
struct rtc_time {int dummy; } ;
struct jz4740_rtc {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  JZ_REG_RTC_SCRATCHPAD ; 
 int /*<<< orphan*/  JZ_REG_RTC_SEC ; 
 struct jz4740_rtc* dev_get_drvdata (struct device*) ; 
 int jz4740_rtc_reg_write (struct jz4740_rtc*,int /*<<< orphan*/ ,int) ; 
 int rtc_tm_to_time64 (struct rtc_time*) ; 

__attribute__((used)) static int jz4740_rtc_set_time(struct device *dev, struct rtc_time *time)
{
	struct jz4740_rtc *rtc = dev_get_drvdata(dev);
	int ret;

	ret = jz4740_rtc_reg_write(rtc, JZ_REG_RTC_SEC, rtc_tm_to_time64(time));
	if (ret)
		return ret;

	return jz4740_rtc_reg_write(rtc, JZ_REG_RTC_SCRATCHPAD, 0x12345678);
}