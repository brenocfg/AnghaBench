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
struct rtc_time {int tm_sec; int tm_min; int tm_hour; int tm_wday; int tm_mday; int tm_mon; int tm_year; } ;
struct ds1343_priv {int /*<<< orphan*/  map; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DS1343_DATE_REG ; 
 int /*<<< orphan*/  DS1343_DAY_REG ; 
 int /*<<< orphan*/  DS1343_HOURS_REG ; 
 int /*<<< orphan*/  DS1343_MINUTES_REG ; 
 int /*<<< orphan*/  DS1343_MONTH_REG ; 
 int /*<<< orphan*/  DS1343_SECONDS_REG ; 
 int /*<<< orphan*/  DS1343_YEAR_REG ; 
 int bin2bcd (int) ; 
 struct ds1343_priv* dev_get_drvdata (struct device*) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ds1343_set_time(struct device *dev, struct rtc_time *dt)
{
	struct ds1343_priv *priv = dev_get_drvdata(dev);
	int res;

	res = regmap_write(priv->map, DS1343_SECONDS_REG,
				bin2bcd(dt->tm_sec));
	if (res)
		return res;

	res = regmap_write(priv->map, DS1343_MINUTES_REG,
				bin2bcd(dt->tm_min));
	if (res)
		return res;

	res = regmap_write(priv->map, DS1343_HOURS_REG,
				bin2bcd(dt->tm_hour) & 0x3F);
	if (res)
		return res;

	res = regmap_write(priv->map, DS1343_DAY_REG,
				bin2bcd(dt->tm_wday + 1));
	if (res)
		return res;

	res = regmap_write(priv->map, DS1343_DATE_REG,
				bin2bcd(dt->tm_mday));
	if (res)
		return res;

	res = regmap_write(priv->map, DS1343_MONTH_REG,
				bin2bcd(dt->tm_mon + 1));
	if (res)
		return res;

	dt->tm_year %= 100;

	res = regmap_write(priv->map, DS1343_YEAR_REG,
				bin2bcd(dt->tm_year));
	if (res)
		return res;

	return 0;
}