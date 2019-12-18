#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int /*<<< orphan*/  time64_t ;
struct rv3028_data {int /*<<< orphan*/  regmap; TYPE_3__* rtc; } ;
struct TYPE_9__ {int tm_sec; int /*<<< orphan*/  tm_mday; int /*<<< orphan*/  tm_hour; int /*<<< orphan*/  tm_min; } ;
struct rtc_wkalrm {scalar_t__ enabled; TYPE_4__ time; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  alarmvals ;
struct TYPE_7__ {scalar_t__ enabled; } ;
struct TYPE_6__ {scalar_t__ enabled; } ;
struct TYPE_8__ {TYPE_2__ aie_timer; TYPE_1__ uie_rtctimer; } ;

/* Variables and functions */
 int /*<<< orphan*/  RV3028_ALARM_MIN ; 
 int /*<<< orphan*/  RV3028_CTRL2 ; 
 int RV3028_CTRL2_AIE ; 
 int RV3028_CTRL2_UIE ; 
 int /*<<< orphan*/  RV3028_STATUS ; 
 int RV3028_STATUS_AF ; 
 int bin2bcd (int /*<<< orphan*/ ) ; 
 struct rv3028_data* dev_get_drvdata (struct device*) ; 
 int regmap_bulk_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  rtc_time64_to_tm (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  rtc_tm_to_time64 (TYPE_4__*) ; 

__attribute__((used)) static int rv3028_set_alarm(struct device *dev, struct rtc_wkalrm *alrm)
{
	struct rv3028_data *rv3028 = dev_get_drvdata(dev);
	u8 alarmvals[3];
	u8 ctrl = 0;
	int ret;

	/* The alarm has no seconds, round up to nearest minute */
	if (alrm->time.tm_sec) {
		time64_t alarm_time = rtc_tm_to_time64(&alrm->time);

		alarm_time += 60 - alrm->time.tm_sec;
		rtc_time64_to_tm(alarm_time, &alrm->time);
	}

	ret = regmap_update_bits(rv3028->regmap, RV3028_CTRL2,
				 RV3028_CTRL2_AIE | RV3028_CTRL2_UIE, 0);
	if (ret)
		return ret;

	alarmvals[0] = bin2bcd(alrm->time.tm_min);
	alarmvals[1] = bin2bcd(alrm->time.tm_hour);
	alarmvals[2] = bin2bcd(alrm->time.tm_mday);

	ret = regmap_update_bits(rv3028->regmap, RV3028_STATUS,
				 RV3028_STATUS_AF, 0);
	if (ret)
		return ret;

	ret = regmap_bulk_write(rv3028->regmap, RV3028_ALARM_MIN, alarmvals,
				sizeof(alarmvals));
	if (ret)
		return ret;

	if (alrm->enabled) {
		if (rv3028->rtc->uie_rtctimer.enabled)
			ctrl |= RV3028_CTRL2_UIE;
		if (rv3028->rtc->aie_timer.enabled)
			ctrl |= RV3028_CTRL2_AIE;
	}

	ret = regmap_update_bits(rv3028->regmap, RV3028_CTRL2,
				 RV3028_CTRL2_UIE | RV3028_CTRL2_AIE, ctrl);

	return ret;
}