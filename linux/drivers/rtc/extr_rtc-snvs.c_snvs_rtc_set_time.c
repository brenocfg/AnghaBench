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
struct snvs_rtc_data {scalar_t__ offset; int /*<<< orphan*/  regmap; } ;
struct rtc_time {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 unsigned long CNTR_TO_SECS_SH ; 
 scalar_t__ SNVS_LPSRTCLR ; 
 scalar_t__ SNVS_LPSRTCMR ; 
 struct snvs_rtc_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,scalar_t__,unsigned long) ; 
 unsigned long rtc_tm_to_time64 (struct rtc_time*) ; 
 int snvs_rtc_enable (struct snvs_rtc_data*,int) ; 

__attribute__((used)) static int snvs_rtc_set_time(struct device *dev, struct rtc_time *tm)
{
	struct snvs_rtc_data *data = dev_get_drvdata(dev);
	unsigned long time = rtc_tm_to_time64(tm);
	int ret;

	/* Disable RTC first */
	ret = snvs_rtc_enable(data, false);
	if (ret)
		return ret;

	/* Write 32-bit time to 47-bit timer, leaving 15 LSBs blank */
	regmap_write(data->regmap, data->offset + SNVS_LPSRTCLR, time << CNTR_TO_SECS_SH);
	regmap_write(data->regmap, data->offset + SNVS_LPSRTCMR, time >> (32 - CNTR_TO_SECS_SH));

	/* Enable RTC again */
	ret = snvs_rtc_enable(data, true);

	return ret;
}