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
struct rtc_time {int tm_year; int tm_sec; int tm_min; int tm_hour; int tm_mday; int tm_mon; int tm_wday; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX6902_REG_CENTURY ; 
 int /*<<< orphan*/  MAX6902_REG_CONTROL ; 
 int /*<<< orphan*/  MAX6902_REG_DATE ; 
 int /*<<< orphan*/  MAX6902_REG_DAY ; 
 int /*<<< orphan*/  MAX6902_REG_HOURS ; 
 int /*<<< orphan*/  MAX6902_REG_MINUTES ; 
 int /*<<< orphan*/  MAX6902_REG_MONTH ; 
 int /*<<< orphan*/  MAX6902_REG_SECONDS ; 
 int /*<<< orphan*/  MAX6902_REG_YEAR ; 
 int bin2bcd (int) ; 
 int /*<<< orphan*/  max6902_set_reg (struct device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int max6902_set_time(struct device *dev, struct rtc_time *dt)
{
	dt->tm_year = dt->tm_year + 1900;

	/* Remove write protection */
	max6902_set_reg(dev, MAX6902_REG_CONTROL, 0);

	max6902_set_reg(dev, MAX6902_REG_SECONDS, bin2bcd(dt->tm_sec));
	max6902_set_reg(dev, MAX6902_REG_MINUTES, bin2bcd(dt->tm_min));
	max6902_set_reg(dev, MAX6902_REG_HOURS, bin2bcd(dt->tm_hour));

	max6902_set_reg(dev, MAX6902_REG_DATE, bin2bcd(dt->tm_mday));
	max6902_set_reg(dev, MAX6902_REG_MONTH, bin2bcd(dt->tm_mon + 1));
	max6902_set_reg(dev, MAX6902_REG_DAY, bin2bcd(dt->tm_wday));
	max6902_set_reg(dev, MAX6902_REG_YEAR, bin2bcd(dt->tm_year % 100));
	max6902_set_reg(dev, MAX6902_REG_CENTURY, bin2bcd(dt->tm_year / 100));

	/* Compulab used a delay here. However, the datasheet
	 * does not mention a delay being required anywhere... */
	/* delay(2000); */

	/* Write protect */
	max6902_set_reg(dev, MAX6902_REG_CONTROL, 0x80);

	return 0;
}