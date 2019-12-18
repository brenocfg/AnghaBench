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
struct spi_device {int dummy; } ;
struct rtc_time {int tm_sec; int tm_min; int tm_hour; int tm_mday; int tm_mon; int tm_wday; int tm_year; } ;
struct regmap {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DS1347_CLOCK_BURST ; 
 int bin2bcd (int) ; 
 int regmap_bulk_write (struct regmap*,int /*<<< orphan*/ ,unsigned char*,int) ; 
 struct regmap* spi_get_drvdata (struct spi_device*) ; 
 struct spi_device* to_spi_device (struct device*) ; 

__attribute__((used)) static int ds1347_set_time(struct device *dev, struct rtc_time *dt)
{
	struct spi_device *spi = to_spi_device(dev);
	struct regmap *map;
	unsigned char buf[8];

	map = spi_get_drvdata(spi);

	buf[0] = bin2bcd(dt->tm_sec);
	buf[1] = bin2bcd(dt->tm_min);
	buf[2] = (bin2bcd(dt->tm_hour) & 0x3F);
	buf[3] = bin2bcd(dt->tm_mday);
	buf[4] = bin2bcd(dt->tm_mon + 1);
	buf[5] = bin2bcd(dt->tm_wday + 1);

	/* year in linux is from 1900 i.e in range of 100
	in rtc it is from 00 to 99 */
	dt->tm_year = dt->tm_year % 100;

	buf[6] = bin2bcd(dt->tm_year);
	buf[7] = bin2bcd(0x00);

	/* write the rtc settings */
	return regmap_bulk_write(map, DS1347_CLOCK_BURST, buf, 8);
}