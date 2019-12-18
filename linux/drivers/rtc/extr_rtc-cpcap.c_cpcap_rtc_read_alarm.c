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
struct rtc_wkalrm {int /*<<< orphan*/  time; int /*<<< orphan*/  enabled; } ;
struct device {int dummy; } ;
struct cpcap_time {int /*<<< orphan*/  tod1; int /*<<< orphan*/  tod2; int /*<<< orphan*/  day; } ;
struct cpcap_rtc {int /*<<< orphan*/  regmap; int /*<<< orphan*/  alarm_enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPCAP_REG_DAYA ; 
 int /*<<< orphan*/  CPCAP_REG_TODA1 ; 
 int /*<<< orphan*/  CPCAP_REG_TODA2 ; 
 int EIO ; 
 int /*<<< orphan*/  cpcap2rtc_time (int /*<<< orphan*/ *,struct cpcap_time*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct cpcap_rtc* dev_get_drvdata (struct device*) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int rtc_valid_tm (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cpcap_rtc_read_alarm(struct device *dev, struct rtc_wkalrm *alrm)
{
	struct cpcap_rtc *rtc;
	struct cpcap_time cpcap_tm;
	int ret;

	rtc = dev_get_drvdata(dev);

	alrm->enabled = rtc->alarm_enabled;

	ret = regmap_read(rtc->regmap, CPCAP_REG_DAYA, &cpcap_tm.day);
	ret |= regmap_read(rtc->regmap, CPCAP_REG_TODA2, &cpcap_tm.tod2);
	ret |= regmap_read(rtc->regmap, CPCAP_REG_TODA1, &cpcap_tm.tod1);

	if (ret) {
		dev_err(dev, "Failed to read time\n");
		return -EIO;
	}

	cpcap2rtc_time(&alrm->time, &cpcap_tm);
	return rtc_valid_tm(&alrm->time);
}