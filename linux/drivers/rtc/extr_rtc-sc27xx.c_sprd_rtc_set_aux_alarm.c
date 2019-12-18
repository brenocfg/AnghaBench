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
typedef  int /*<<< orphan*/  time64_t ;
struct sprd_rtc {scalar_t__ base; int /*<<< orphan*/  regmap; } ;
struct rtc_wkalrm {scalar_t__ enabled; int /*<<< orphan*/  time; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPRD_RTC_AUXALM_EN ; 
 int /*<<< orphan*/  SPRD_RTC_AUX_ALARM ; 
 scalar_t__ SPRD_RTC_INT_CLR ; 
 scalar_t__ SPRD_RTC_INT_EN ; 
 struct sprd_rtc* dev_get_drvdata (struct device*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int regmap_write (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtc_tm_to_time64 (int /*<<< orphan*/ *) ; 
 int sprd_rtc_set_secs (struct sprd_rtc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sprd_rtc_set_aux_alarm(struct device *dev, struct rtc_wkalrm *alrm)
{
	struct sprd_rtc *rtc = dev_get_drvdata(dev);
	time64_t secs = rtc_tm_to_time64(&alrm->time);
	int ret;

	/* clear the auxiliary alarm interrupt status */
	ret = regmap_write(rtc->regmap, rtc->base + SPRD_RTC_INT_CLR,
			   SPRD_RTC_AUXALM_EN);
	if (ret)
		return ret;

	ret = sprd_rtc_set_secs(rtc, SPRD_RTC_AUX_ALARM, secs);
	if (ret)
		return ret;

	if (alrm->enabled) {
		ret = regmap_update_bits(rtc->regmap,
					 rtc->base + SPRD_RTC_INT_EN,
					 SPRD_RTC_AUXALM_EN,
					 SPRD_RTC_AUXALM_EN);
	} else {
		ret = regmap_update_bits(rtc->regmap,
					 rtc->base + SPRD_RTC_INT_EN,
					 SPRD_RTC_AUXALM_EN, 0);
	}

	return ret;
}