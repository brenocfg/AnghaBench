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
struct rtc_time {scalar_t__ tm_year; scalar_t__ tm_mon; scalar_t__ tm_wday; scalar_t__ tm_mday; scalar_t__ tm_hour; scalar_t__ tm_min; scalar_t__ tm_sec; } ;
struct regmap {int dummy; } ;
struct device {int dummy; } ;
struct abeoz9_rtc_data {struct regmap* regmap; } ;
typedef  int /*<<< orphan*/  regs ;

/* Variables and functions */
 size_t ABEOZ9_REG_DAYS ; 
 size_t ABEOZ9_REG_HOURS ; 
 size_t ABEOZ9_REG_MIN ; 
 size_t ABEOZ9_REG_MONTHS ; 
 size_t ABEOZ9_REG_SEC ; 
 size_t ABEOZ9_REG_WEEKDAYS ; 
 size_t ABEOZ9_REG_YEARS ; 
 int ABEOZ9_SEC_LEN ; 
 int abeoz9_reset_validity (struct regmap*) ; 
 int /*<<< orphan*/  bin2bcd (scalar_t__) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 struct abeoz9_rtc_data* dev_get_drvdata (struct device*) ; 
 int regmap_bulk_write (struct regmap*,size_t,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int abeoz9_rtc_set_time(struct device *dev, struct rtc_time *tm)
{
	struct abeoz9_rtc_data *data = dev_get_drvdata(dev);
	struct regmap *regmap = data->regmap;
	u8 regs[ABEOZ9_SEC_LEN];
	int ret;

	regs[ABEOZ9_REG_SEC - ABEOZ9_REG_SEC] = bin2bcd(tm->tm_sec);
	regs[ABEOZ9_REG_MIN - ABEOZ9_REG_SEC] = bin2bcd(tm->tm_min);
	regs[ABEOZ9_REG_HOURS - ABEOZ9_REG_SEC] = bin2bcd(tm->tm_hour);
	regs[ABEOZ9_REG_DAYS - ABEOZ9_REG_SEC] = bin2bcd(tm->tm_mday);
	regs[ABEOZ9_REG_WEEKDAYS - ABEOZ9_REG_SEC] = bin2bcd(tm->tm_wday);
	regs[ABEOZ9_REG_MONTHS - ABEOZ9_REG_SEC] = bin2bcd(tm->tm_mon + 1);
	regs[ABEOZ9_REG_YEARS - ABEOZ9_REG_SEC] = bin2bcd(tm->tm_year - 100);

	ret = regmap_bulk_write(data->regmap, ABEOZ9_REG_SEC,
				regs,
				sizeof(regs));

	if (ret) {
		dev_err(dev, "set RTC time failed (%d)\n", ret);
		return ret;
	}

	return abeoz9_reset_validity(regmap);
}