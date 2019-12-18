#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct device {int dummy; } ;
struct bd70528_rtc {TYPE_1__* mfd; } ;
struct TYPE_4__ {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 unsigned int BD70528_MASK_ALM_EN ; 
 int /*<<< orphan*/  BD70528_REG_RTC_ALM_MASK ; 
 int bd70528_set_wake (TYPE_1__*,unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bd70528_wdt_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  bd70528_wdt_unlock (TYPE_1__*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct bd70528_rtc* dev_get_drvdata (struct device*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 

__attribute__((used)) static int bd70528_alm_enable(struct device *dev, unsigned int enabled)
{
	int ret;
	unsigned int enableval = BD70528_MASK_ALM_EN;
	struct bd70528_rtc *r = dev_get_drvdata(dev);

	if (enabled)
		enableval = 0;

	bd70528_wdt_lock(r->mfd);
	ret = bd70528_set_wake(r->mfd, enabled, NULL);
	if (ret) {
		dev_err(dev, "Failed to change wake state\n");
		goto out_unlock;
	}
	ret = regmap_update_bits(r->mfd->regmap, BD70528_REG_RTC_ALM_MASK,
				 BD70528_MASK_ALM_EN, enableval);
	if (ret)
		dev_err(dev, "Failed to change alarm state\n");

out_unlock:
	bd70528_wdt_unlock(r->mfd);
	return ret;
}