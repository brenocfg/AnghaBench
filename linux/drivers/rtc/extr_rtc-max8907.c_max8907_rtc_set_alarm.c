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
typedef  int /*<<< orphan*/  u8 ;
struct rtc_wkalrm {scalar_t__ enabled; int /*<<< orphan*/  time; } ;
struct max8907_rtc {int /*<<< orphan*/  regmap; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX8907_REG_ALARM0_CNTL ; 
 int /*<<< orphan*/  MAX8907_REG_ALARM0_SEC ; 
 int TIME_NUM ; 
 struct max8907_rtc* dev_get_drvdata (struct device*) ; 
 int regmap_bulk_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tm_to_regs (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int max8907_rtc_set_alarm(struct device *dev, struct rtc_wkalrm *alrm)
{
	struct max8907_rtc *rtc = dev_get_drvdata(dev);
	u8 regs[TIME_NUM];
	int ret;

	tm_to_regs(&alrm->time, regs);

	/* Disable alarm while we update the target time */
	ret = regmap_write(rtc->regmap, MAX8907_REG_ALARM0_CNTL, 0);
	if (ret < 0)
		return ret;

	ret = regmap_bulk_write(rtc->regmap, MAX8907_REG_ALARM0_SEC, regs,
				TIME_NUM);
	if (ret < 0)
		return ret;

	if (alrm->enabled)
		ret = regmap_write(rtc->regmap, MAX8907_REG_ALARM0_CNTL, 0x77);

	return ret;
}