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
struct spi_device {int /*<<< orphan*/  dev; } ;
struct rtc_time {int tm_year; int tm_sec; int tm_min; int tm_hour; int tm_mday; int tm_mon; int tm_wday; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int MAX6916_CLOCK_BURST ; 
 int bin2bcd (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int spi_write_then_read (struct spi_device*,unsigned char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct spi_device* to_spi_device (struct device*) ; 

__attribute__((used)) static int max6916_set_time(struct device *dev, struct rtc_time *dt)
{
	struct spi_device *spi = to_spi_device(dev);
	unsigned char buf[9];

	if (dt->tm_year < 100 || dt->tm_year > 199) {
		dev_err(&spi->dev, "Year must be between 2000 and 2099. It's %d.\n",
			dt->tm_year + 1900);
		return -EINVAL;
	}

	buf[0] = MAX6916_CLOCK_BURST & 0x7F;
	buf[1] = bin2bcd(dt->tm_sec);
	buf[2] = bin2bcd(dt->tm_min);
	buf[3] = (bin2bcd(dt->tm_hour) & 0X3F);
	buf[4] = bin2bcd(dt->tm_mday);
	buf[5] = bin2bcd(dt->tm_mon + 1);
	buf[6] = bin2bcd(dt->tm_wday + 1);
	buf[7] = bin2bcd(dt->tm_year % 100);
	buf[8] = bin2bcd(0x00);

	/* write the rtc settings */
	return spi_write_then_read(spi, buf, 9, NULL, 0);
}