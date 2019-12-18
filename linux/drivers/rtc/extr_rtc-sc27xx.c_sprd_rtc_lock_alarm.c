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
struct sprd_rtc {scalar_t__ base; int /*<<< orphan*/  regmap; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int SPRD_RTC_ALMLOCK_MASK ; 
 int SPRD_RTC_ALM_LOCK ; 
 int SPRD_RTC_ALM_UNLOCK ; 
 scalar_t__ SPRD_RTC_INT_CLR ; 
 scalar_t__ SPRD_RTC_INT_RAW_STS ; 
 int /*<<< orphan*/  SPRD_RTC_POLL_DELAY_US ; 
 int /*<<< orphan*/  SPRD_RTC_POLL_TIMEOUT ; 
 int SPRD_RTC_POWEROFF_ALM_FLAG ; 
 scalar_t__ SPRD_RTC_SPG_UPD ; 
 int SPRD_RTC_SPG_UPD_EN ; 
 scalar_t__ SPRD_RTC_SPG_VALUE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int regmap_read (int /*<<< orphan*/ ,scalar_t__,int*) ; 
 int regmap_read_poll_timeout (int /*<<< orphan*/ ,scalar_t__,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int regmap_write (int /*<<< orphan*/ ,scalar_t__,int) ; 

__attribute__((used)) static int sprd_rtc_lock_alarm(struct sprd_rtc *rtc, bool lock)
{
	int ret;
	u32 val;

	ret = regmap_read(rtc->regmap, rtc->base + SPRD_RTC_SPG_VALUE, &val);
	if (ret)
		return ret;

	val &= ~SPRD_RTC_ALMLOCK_MASK;
	if (lock)
		val |= SPRD_RTC_ALM_LOCK;
	else
		val |= SPRD_RTC_ALM_UNLOCK | SPRD_RTC_POWEROFF_ALM_FLAG;

	ret = regmap_write(rtc->regmap, rtc->base + SPRD_RTC_SPG_UPD, val);
	if (ret)
		return ret;

	/* wait until the SPG value is updated successfully */
	ret = regmap_read_poll_timeout(rtc->regmap,
				       rtc->base + SPRD_RTC_INT_RAW_STS, val,
				       (val & SPRD_RTC_SPG_UPD_EN),
				       SPRD_RTC_POLL_DELAY_US,
				       SPRD_RTC_POLL_TIMEOUT);
	if (ret) {
		dev_err(rtc->dev, "failed to update SPG value:%d\n", ret);
		return ret;
	}

	return regmap_write(rtc->regmap, rtc->base + SPRD_RTC_INT_CLR,
			    SPRD_RTC_SPG_UPD_EN);
}