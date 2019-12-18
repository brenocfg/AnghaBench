#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct sunxi_rtc_dev {scalar_t__ base; TYPE_1__* data_year; } ;
struct rtc_time {int tm_mon; int /*<<< orphan*/  tm_year; int /*<<< orphan*/  tm_mday; int /*<<< orphan*/  tm_hour; int /*<<< orphan*/  tm_min; int /*<<< orphan*/  tm_sec; } ;
struct rtc_wkalrm {int enabled; struct rtc_time time; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  mask; } ;

/* Variables and functions */
 scalar_t__ SUNXI_ALRM_DHMS ; 
 int SUNXI_ALRM_EN_CNT_EN ; 
 int /*<<< orphan*/  SUNXI_ALRM_GET_HOUR_VALUE (int) ; 
 int /*<<< orphan*/  SUNXI_ALRM_GET_MIN_VALUE (int) ; 
 int /*<<< orphan*/  SUNXI_ALRM_GET_SEC_VALUE (int) ; 
 scalar_t__ SUNXI_ALRM_IRQ_EN ; 
 int /*<<< orphan*/  SUNXI_DATE_GET_DAY_VALUE (int) ; 
 int SUNXI_DATE_GET_MON_VALUE (int) ; 
 int /*<<< orphan*/  SUNXI_DATE_GET_YEAR_VALUE (int,int /*<<< orphan*/ ) ; 
 scalar_t__ SUNXI_RTC_YMD ; 
 scalar_t__ SUNXI_YEAR_OFF (TYPE_1__*) ; 
 struct sunxi_rtc_dev* dev_get_drvdata (struct device*) ; 
 int readl (scalar_t__) ; 

__attribute__((used)) static int sunxi_rtc_getalarm(struct device *dev, struct rtc_wkalrm *wkalrm)
{
	struct sunxi_rtc_dev *chip = dev_get_drvdata(dev);
	struct rtc_time *alrm_tm = &wkalrm->time;
	u32 alrm;
	u32 alrm_en;
	u32 date;

	alrm = readl(chip->base + SUNXI_ALRM_DHMS);
	date = readl(chip->base + SUNXI_RTC_YMD);

	alrm_tm->tm_sec = SUNXI_ALRM_GET_SEC_VALUE(alrm);
	alrm_tm->tm_min = SUNXI_ALRM_GET_MIN_VALUE(alrm);
	alrm_tm->tm_hour = SUNXI_ALRM_GET_HOUR_VALUE(alrm);

	alrm_tm->tm_mday = SUNXI_DATE_GET_DAY_VALUE(date);
	alrm_tm->tm_mon = SUNXI_DATE_GET_MON_VALUE(date);
	alrm_tm->tm_year = SUNXI_DATE_GET_YEAR_VALUE(date,
			chip->data_year->mask);

	alrm_tm->tm_mon -= 1;

	/*
	 * switch from (data_year->min)-relative offset to
	 * a (1900)-relative one
	 */
	alrm_tm->tm_year += SUNXI_YEAR_OFF(chip->data_year);

	alrm_en = readl(chip->base + SUNXI_ALRM_IRQ_EN);
	if (alrm_en & SUNXI_ALRM_EN_CNT_EN)
		wkalrm->enabled = 1;

	return 0;
}