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
struct rtc_wkalrm {int enabled; int /*<<< orphan*/  time; } ;
struct max8907_rtc {int /*<<< orphan*/  regmap; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX8907_REG_ALARM0_CNTL ; 
 int /*<<< orphan*/  MAX8907_REG_ALARM0_SEC ; 
 int TIME_NUM ; 
 struct max8907_rtc* dev_get_drvdata (struct device*) ; 
 int regmap_bulk_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  regs_to_tm (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int max8907_rtc_read_alarm(struct device *dev, struct rtc_wkalrm *alrm)
{
	struct max8907_rtc *rtc = dev_get_drvdata(dev);
	u8 regs[TIME_NUM];
	unsigned int val;
	int ret;

	ret = regmap_bulk_read(rtc->regmap, MAX8907_REG_ALARM0_SEC, regs,
			       TIME_NUM);
	if (ret < 0)
		return ret;

	regs_to_tm(regs, &alrm->time);

	ret = regmap_read(rtc->regmap, MAX8907_REG_ALARM0_CNTL, &val);
	if (ret < 0)
		return ret;

	alrm->enabled = !!(val & 0x7f);

	return 0;
}