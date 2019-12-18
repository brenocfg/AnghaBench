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
typedef  int /*<<< orphan*/  wake ;
struct rtc_wkalrm {scalar_t__ enabled; int /*<<< orphan*/  time; } ;
struct rohm_regmap_dev {int /*<<< orphan*/  regmap; } ;
struct device {int dummy; } ;
struct bd70528_rtc_wake {int /*<<< orphan*/  ctrl; int /*<<< orphan*/  alm_mask; int /*<<< orphan*/  time; int /*<<< orphan*/  data; } ;
struct bd70528_rtc_alm {int /*<<< orphan*/  ctrl; int /*<<< orphan*/  alm_mask; int /*<<< orphan*/  time; int /*<<< orphan*/  data; } ;
struct bd70528_rtc {struct rohm_regmap_dev* mfd; } ;
typedef  int /*<<< orphan*/  alm ;

/* Variables and functions */
 int /*<<< orphan*/  BD70528_MASK_ALM_EN ; 
 int /*<<< orphan*/  BD70528_MASK_WAKE_EN ; 
 int /*<<< orphan*/  BD70528_REG_RTC_ALM_START ; 
 int /*<<< orphan*/  BD70528_REG_RTC_WAKE_START ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct bd70528_rtc* dev_get_drvdata (struct device*) ; 
 int regmap_bulk_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct bd70528_rtc_wake*,int) ; 
 int regmap_bulk_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct bd70528_rtc_wake*,int) ; 
 int /*<<< orphan*/  tm2rtc (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tmday2rtc (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bd70528_set_alarm(struct device *dev, struct rtc_wkalrm *a)
{
	struct bd70528_rtc_wake wake;
	struct bd70528_rtc_alm alm;
	int ret;
	struct bd70528_rtc *r = dev_get_drvdata(dev);
	struct rohm_regmap_dev *bd70528 = r->mfd;

	ret = regmap_bulk_read(bd70528->regmap, BD70528_REG_RTC_WAKE_START,
			       &wake, sizeof(wake));
	if (ret) {
		dev_err(dev, "Failed to read wake regs\n");
		return ret;
	}

	ret = regmap_bulk_read(bd70528->regmap, BD70528_REG_RTC_ALM_START,
			       &alm, sizeof(alm));
	if (ret) {
		dev_err(dev, "Failed to read alarm regs\n");
		return ret;
	}

	tm2rtc(&a->time, &alm.data);
	tmday2rtc(&a->time, &wake.time);

	if (a->enabled) {
		alm.alm_mask &= ~BD70528_MASK_ALM_EN;
		wake.ctrl |= BD70528_MASK_WAKE_EN;
	} else {
		alm.alm_mask |= BD70528_MASK_ALM_EN;
		wake.ctrl &= ~BD70528_MASK_WAKE_EN;
	}

	ret = regmap_bulk_write(bd70528->regmap,
				BD70528_REG_RTC_WAKE_START, &wake,
				sizeof(wake));
	if (ret) {
		dev_err(dev, "Failed to set wake time\n");
		return ret;
	}
	ret = regmap_bulk_write(bd70528->regmap, BD70528_REG_RTC_ALM_START,
				&alm, sizeof(alm));
	if (ret)
		dev_err(dev, "Failed to set alarm time\n");

	return ret;
}