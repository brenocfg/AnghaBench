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
struct spi_device {int dummy; } ;
struct rtc_time {int tm_wday; void* tm_year; void* tm_mon; void* tm_mday; void* tm_hour; void* tm_min; void* tm_sec; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  addr ;

/* Variables and functions */
 size_t RTC_ADDR_DATE ; 
 size_t RTC_ADDR_DAY ; 
 size_t RTC_ADDR_HOUR ; 
 size_t RTC_ADDR_MIN ; 
 size_t RTC_ADDR_MON ; 
 size_t RTC_ADDR_SEC ; 
 size_t RTC_ADDR_YEAR ; 
 int RTC_CLCK_BURST ; 
 int /*<<< orphan*/  RTC_CLCK_LEN ; 
 int RTC_CMD_READ ; 
 void* bcd2bin (int) ; 
 struct spi_device* dev_get_drvdata (struct device*) ; 
 int spi_write_then_read (struct spi_device*,int*,int,int*,int) ; 

__attribute__((used)) static int ds1302_rtc_get_time(struct device *dev, struct rtc_time *time)
{
	struct spi_device	*spi = dev_get_drvdata(dev);
	u8		addr = RTC_CLCK_BURST << 1 | RTC_CMD_READ;
	u8		buf[RTC_CLCK_LEN - 1];
	int		status;

	/* Use write-then-read to get all the date/time registers
	 * since dma from stack is nonportable
	 */
	status = spi_write_then_read(spi, &addr, sizeof(addr),
			buf, sizeof(buf));
	if (status < 0)
		return status;

	/* Decode the registers */
	time->tm_sec = bcd2bin(buf[RTC_ADDR_SEC]);
	time->tm_min = bcd2bin(buf[RTC_ADDR_MIN]);
	time->tm_hour = bcd2bin(buf[RTC_ADDR_HOUR]);
	time->tm_wday = buf[RTC_ADDR_DAY] - 1;
	time->tm_mday = bcd2bin(buf[RTC_ADDR_DATE]);
	time->tm_mon = bcd2bin(buf[RTC_ADDR_MON]) - 1;
	time->tm_year = bcd2bin(buf[RTC_ADDR_YEAR]) + 100;

	return 0;
}