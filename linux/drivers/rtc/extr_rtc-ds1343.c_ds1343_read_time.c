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
struct rtc_time {void* tm_year; void* tm_mon; void* tm_mday; void* tm_wday; void* tm_hour; void* tm_min; void* tm_sec; } ;
struct ds1343_priv {int /*<<< orphan*/  map; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DS1343_SECONDS_REG ; 
 void* bcd2bin (unsigned char) ; 
 struct ds1343_priv* dev_get_drvdata (struct device*) ; 
 int regmap_bulk_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,int) ; 

__attribute__((used)) static int ds1343_read_time(struct device *dev, struct rtc_time *dt)
{
	struct ds1343_priv *priv = dev_get_drvdata(dev);
	unsigned char buf[7];
	int res;

	res = regmap_bulk_read(priv->map, DS1343_SECONDS_REG, buf, 7);
	if (res)
		return res;

	dt->tm_sec	= bcd2bin(buf[0]);
	dt->tm_min	= bcd2bin(buf[1]);
	dt->tm_hour	= bcd2bin(buf[2] & 0x3F);
	dt->tm_wday	= bcd2bin(buf[3]) - 1;
	dt->tm_mday	= bcd2bin(buf[4]);
	dt->tm_mon	= bcd2bin(buf[5] & 0x1F) - 1;
	dt->tm_year	= bcd2bin(buf[6]) + 100; /* year offset from 1900 */

	return 0;
}