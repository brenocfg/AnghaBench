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
typedef  int u8 ;
struct rtc_time {int tm_hour; void* tm_year; void* tm_mon; void* tm_wday; void* tm_mday; void* tm_min; void* tm_sec; } ;
struct device {int dummy; } ;
struct abeoz9_rtc_data {int /*<<< orphan*/  regmap; } ;
typedef  int /*<<< orphan*/  regs ;

/* Variables and functions */
 int ABEOZ9_HOURS_PM ; 
 size_t ABEOZ9_REG_DAYS ; 
 size_t ABEOZ9_REG_HOURS ; 
 size_t ABEOZ9_REG_MIN ; 
 size_t ABEOZ9_REG_MONTHS ; 
 size_t ABEOZ9_REG_SEC ; 
 size_t ABEOZ9_REG_WEEKDAYS ; 
 size_t ABEOZ9_REG_YEARS ; 
 int ABEOZ9_SEC_LEN ; 
 int abeoz9_check_validity (struct device*) ; 
 void* bcd2bin (int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 struct abeoz9_rtc_data* dev_get_drvdata (struct device*) ; 
 int regmap_bulk_read (int /*<<< orphan*/ ,size_t,int*,int) ; 

__attribute__((used)) static int abeoz9_rtc_get_time(struct device *dev, struct rtc_time *tm)
{
	struct abeoz9_rtc_data *data = dev_get_drvdata(dev);
	u8 regs[ABEOZ9_SEC_LEN];
	int ret;

	ret = abeoz9_check_validity(dev);
	if (ret)
		return ret;

	ret = regmap_bulk_read(data->regmap, ABEOZ9_REG_SEC,
			       regs,
			       sizeof(regs));
	if (ret) {
		dev_err(dev, "reading RTC time failed (%d)\n", ret);
		return ret;
	}

	tm->tm_sec = bcd2bin(regs[ABEOZ9_REG_SEC - ABEOZ9_REG_SEC] & 0x7F);
	tm->tm_min = bcd2bin(regs[ABEOZ9_REG_MIN - ABEOZ9_REG_SEC] & 0x7F);

	if (regs[ABEOZ9_REG_HOURS - ABEOZ9_REG_SEC] & ABEOZ9_HOURS_PM) {
		tm->tm_hour =
			bcd2bin(regs[ABEOZ9_REG_HOURS - ABEOZ9_REG_SEC] & 0x1f);
		if (regs[ABEOZ9_REG_HOURS - ABEOZ9_REG_SEC] & ABEOZ9_HOURS_PM)
			tm->tm_hour += 12;
	} else {
		tm->tm_hour = bcd2bin(regs[ABEOZ9_REG_HOURS - ABEOZ9_REG_SEC]);
	}

	tm->tm_mday = bcd2bin(regs[ABEOZ9_REG_DAYS - ABEOZ9_REG_SEC]);
	tm->tm_wday = bcd2bin(regs[ABEOZ9_REG_WEEKDAYS - ABEOZ9_REG_SEC]);
	tm->tm_mon  = bcd2bin(regs[ABEOZ9_REG_MONTHS - ABEOZ9_REG_SEC]) - 1;
	tm->tm_year = bcd2bin(regs[ABEOZ9_REG_YEARS - ABEOZ9_REG_SEC]) + 100;

	return ret;
}