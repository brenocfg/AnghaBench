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
struct rtc_time {int tm_sec; int tm_min; int tm_hour; int tm_mon; int tm_mday; int tm_year; } ;
struct rtc_wkalrm {int enabled; struct rtc_time time; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ S3C2410_ALMDATE ; 
 scalar_t__ S3C2410_ALMHOUR ; 
 scalar_t__ S3C2410_ALMMIN ; 
 scalar_t__ S3C2410_ALMMON ; 
 scalar_t__ S3C2410_ALMSEC ; 
 scalar_t__ S3C2410_ALMYEAR ; 
 scalar_t__ S3C2410_RTCALM ; 
 unsigned int S3C2410_RTCALM_ALMEN ; 
 unsigned int S3C2410_RTCALM_DAYEN ; 
 unsigned int S3C2410_RTCALM_HOUREN ; 
 unsigned int S3C2410_RTCALM_MINEN ; 
 unsigned int S3C2410_RTCALM_MONEN ; 
 unsigned int S3C2410_RTCALM_SECEN ; 
 unsigned int S3C2410_RTCALM_YEAREN ; 
 void* bcd2bin (int) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,unsigned int,struct rtc_time*) ; 
 struct s3c_rtc* dev_get_drvdata (struct device*) ; 
 void* readb (scalar_t__) ; 
 int /*<<< orphan*/  s3c_rtc_disable_clk (struct s3c_rtc*) ; 
 int s3c_rtc_enable_clk (struct s3c_rtc*) ; 

__attribute__((used)) static int s3c_rtc_getalarm(struct device *dev, struct rtc_wkalrm *alrm)
{
	struct s3c_rtc *info = dev_get_drvdata(dev);
	struct rtc_time *alm_tm = &alrm->time;
	unsigned int alm_en;
	int ret;

	ret = s3c_rtc_enable_clk(info);
	if (ret)
		return ret;

	alm_tm->tm_sec  = readb(info->base + S3C2410_ALMSEC);
	alm_tm->tm_min  = readb(info->base + S3C2410_ALMMIN);
	alm_tm->tm_hour = readb(info->base + S3C2410_ALMHOUR);
	alm_tm->tm_mon  = readb(info->base + S3C2410_ALMMON);
	alm_tm->tm_mday = readb(info->base + S3C2410_ALMDATE);
	alm_tm->tm_year = readb(info->base + S3C2410_ALMYEAR);

	alm_en = readb(info->base + S3C2410_RTCALM);

	s3c_rtc_disable_clk(info);

	alrm->enabled = (alm_en & S3C2410_RTCALM_ALMEN) ? 1 : 0;

	dev_dbg(dev, "read alarm %d, %ptR\n", alm_en, alm_tm);

	/* decode the alarm enable field */
	if (alm_en & S3C2410_RTCALM_SECEN)
		alm_tm->tm_sec = bcd2bin(alm_tm->tm_sec);

	if (alm_en & S3C2410_RTCALM_MINEN)
		alm_tm->tm_min = bcd2bin(alm_tm->tm_min);

	if (alm_en & S3C2410_RTCALM_HOUREN)
		alm_tm->tm_hour = bcd2bin(alm_tm->tm_hour);

	if (alm_en & S3C2410_RTCALM_DAYEN)
		alm_tm->tm_mday = bcd2bin(alm_tm->tm_mday);

	if (alm_en & S3C2410_RTCALM_MONEN) {
		alm_tm->tm_mon = bcd2bin(alm_tm->tm_mon);
		alm_tm->tm_mon -= 1;
	}

	if (alm_en & S3C2410_RTCALM_YEAREN)
		alm_tm->tm_year = bcd2bin(alm_tm->tm_year);

	return 0;
}