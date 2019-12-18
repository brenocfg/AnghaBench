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
struct s3c_rtc {scalar_t__ base; } ;
struct rtc_time {int tm_year; int tm_sec; int tm_min; int tm_hour; int tm_mday; int tm_mon; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ S3C2410_RTCDATE ; 
 scalar_t__ S3C2410_RTCHOUR ; 
 scalar_t__ S3C2410_RTCMIN ; 
 scalar_t__ S3C2410_RTCMON ; 
 scalar_t__ S3C2410_RTCSEC ; 
 scalar_t__ S3C2410_RTCYEAR ; 
 int /*<<< orphan*/  bin2bcd (int) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,struct rtc_time*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct s3c_rtc* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  s3c_rtc_disable_clk (struct s3c_rtc*) ; 
 int s3c_rtc_enable_clk (struct s3c_rtc*) ; 
 int /*<<< orphan*/  writeb (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int s3c_rtc_settime(struct device *dev, struct rtc_time *tm)
{
	struct s3c_rtc *info = dev_get_drvdata(dev);
	int year = tm->tm_year - 100;
	int ret;

	dev_dbg(dev, "set time %ptR\n", tm);

	/* we get around y2k by simply not supporting it */

	if (year < 0 || year >= 100) {
		dev_err(dev, "rtc only supports 100 years\n");
		return -EINVAL;
	}

	ret = s3c_rtc_enable_clk(info);
	if (ret)
		return ret;

	writeb(bin2bcd(tm->tm_sec),  info->base + S3C2410_RTCSEC);
	writeb(bin2bcd(tm->tm_min),  info->base + S3C2410_RTCMIN);
	writeb(bin2bcd(tm->tm_hour), info->base + S3C2410_RTCHOUR);
	writeb(bin2bcd(tm->tm_mday), info->base + S3C2410_RTCDATE);
	writeb(bin2bcd(tm->tm_mon + 1), info->base + S3C2410_RTCMON);
	writeb(bin2bcd(year), info->base + S3C2410_RTCYEAR);

	s3c_rtc_disable_clk(info);

	return 0;
}