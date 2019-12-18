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
struct rtc_time {void* tm_year; void* tm_wday; void* tm_mon; void* tm_mday; void* tm_hour; void* tm_min; void* tm_sec; } ;
struct regmap {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DS1347_CLOCK_BURST ; 
 void* bcd2bin (unsigned char) ; 
 int regmap_bulk_read (struct regmap*,int /*<<< orphan*/ ,unsigned char*,int) ; 
 struct regmap* spi_get_drvdata (struct spi_device*) ; 
 struct spi_device* to_spi_device (struct device*) ; 

__attribute__((used)) static int ds1347_read_time(struct device *dev, struct rtc_time *dt)
{
	struct spi_device *spi = to_spi_device(dev);
	struct regmap *map;
	int err;
	unsigned char buf[8];

	map = spi_get_drvdata(spi);

	err = regmap_bulk_read(map, DS1347_CLOCK_BURST, buf, 8);
	if (err)
		return err;

	dt->tm_sec = bcd2bin(buf[0]);
	dt->tm_min = bcd2bin(buf[1]);
	dt->tm_hour = bcd2bin(buf[2] & 0x3F);
	dt->tm_mday = bcd2bin(buf[3]);
	dt->tm_mon = bcd2bin(buf[4]) - 1;
	dt->tm_wday = bcd2bin(buf[5]) - 1;
	dt->tm_year = bcd2bin(buf[6]) + 100;

	return 0;
}