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
struct rtc_time {int tm_sec; int tm_min; int tm_hour; int tm_mon; int tm_mday; } ;
struct rtc_wkalrm {int /*<<< orphan*/  enabled; struct rtc_time time; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ S3C2410_ALMDATE ; 
 scalar_t__ S3C2410_ALMHOUR ; 
 scalar_t__ S3C2410_ALMMIN ; 
 scalar_t__ S3C2410_ALMMON ; 
 scalar_t__ S3C2410_ALMSEC ; 
 scalar_t__ S3C2410_RTCALM ; 
 unsigned int S3C2410_RTCALM_ALMEN ; 
 unsigned int S3C2410_RTCALM_DAYEN ; 
 unsigned int S3C2410_RTCALM_HOUREN ; 
 unsigned int S3C2410_RTCALM_MINEN ; 
 unsigned int S3C2410_RTCALM_MONEN ; 
 unsigned int S3C2410_RTCALM_SECEN ; 
 unsigned int bin2bcd (int) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,unsigned int,...) ; 
 struct s3c_rtc* dev_get_drvdata (struct device*) ; 
 unsigned int readb (scalar_t__) ; 
 int /*<<< orphan*/  s3c_rtc_disable_clk (struct s3c_rtc*) ; 
 int s3c_rtc_enable_clk (struct s3c_rtc*) ; 
 int /*<<< orphan*/  s3c_rtc_setaie (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writeb (unsigned int,scalar_t__) ; 

__attribute__((used)) static int s3c_rtc_setalarm(struct device *dev, struct rtc_wkalrm *alrm)
{
	struct s3c_rtc *info = dev_get_drvdata(dev);
	struct rtc_time *tm = &alrm->time;
	unsigned int alrm_en;
	int ret;

	dev_dbg(dev, "s3c_rtc_setalarm: %d, %ptR\n", alrm->enabled, tm);

	ret = s3c_rtc_enable_clk(info);
	if (ret)
		return ret;

	alrm_en = readb(info->base + S3C2410_RTCALM) & S3C2410_RTCALM_ALMEN;
	writeb(0x00, info->base + S3C2410_RTCALM);

	if (tm->tm_sec < 60 && tm->tm_sec >= 0) {
		alrm_en |= S3C2410_RTCALM_SECEN;
		writeb(bin2bcd(tm->tm_sec), info->base + S3C2410_ALMSEC);
	}

	if (tm->tm_min < 60 && tm->tm_min >= 0) {
		alrm_en |= S3C2410_RTCALM_MINEN;
		writeb(bin2bcd(tm->tm_min), info->base + S3C2410_ALMMIN);
	}

	if (tm->tm_hour < 24 && tm->tm_hour >= 0) {
		alrm_en |= S3C2410_RTCALM_HOUREN;
		writeb(bin2bcd(tm->tm_hour), info->base + S3C2410_ALMHOUR);
	}

	if (tm->tm_mon < 12 && tm->tm_mon >= 0) {
		alrm_en |= S3C2410_RTCALM_MONEN;
		writeb(bin2bcd(tm->tm_mon + 1), info->base + S3C2410_ALMMON);
	}

	if (tm->tm_mday <= 31 && tm->tm_mday >= 1) {
		alrm_en |= S3C2410_RTCALM_DAYEN;
		writeb(bin2bcd(tm->tm_mday), info->base + S3C2410_ALMDATE);
	}

	dev_dbg(dev, "setting S3C2410_RTCALM to %08x\n", alrm_en);

	writeb(alrm_en, info->base + S3C2410_RTCALM);

	s3c_rtc_setaie(dev, alrm->enabled);

	s3c_rtc_disable_clk(info);

	return 0;
}