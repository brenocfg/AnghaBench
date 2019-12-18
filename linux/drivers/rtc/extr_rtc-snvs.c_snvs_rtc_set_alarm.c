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
struct rtc_wkalrm {int /*<<< orphan*/  enabled; int /*<<< orphan*/  time; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ SNVS_LPCR ; 
 int /*<<< orphan*/  SNVS_LPCR_LPTA_EN ; 
 scalar_t__ SNVS_LPSR ; 
 unsigned long SNVS_LPSR_LPTA ; 
 scalar_t__ SNVS_LPTAR ; 
 struct snvs_rtc_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,scalar_t__,unsigned long) ; 
 unsigned long rtc_tm_to_time64 (int /*<<< orphan*/ *) ; 
 int rtc_write_sync_lp (struct snvs_rtc_data*) ; 
 int snvs_rtc_alarm_irq_enable (struct device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snvs_rtc_set_alarm(struct device *dev, struct rtc_wkalrm *alrm)
{
	struct snvs_rtc_data *data = dev_get_drvdata(dev);
	unsigned long time = rtc_tm_to_time64(&alrm->time);
	int ret;

	regmap_update_bits(data->regmap, data->offset + SNVS_LPCR, SNVS_LPCR_LPTA_EN, 0);
	ret = rtc_write_sync_lp(data);
	if (ret)
		return ret;
	regmap_write(data->regmap, data->offset + SNVS_LPTAR, time);

	/* Clear alarm interrupt status bit */
	regmap_write(data->regmap, data->offset + SNVS_LPSR, SNVS_LPSR_LPTA);

	return snvs_rtc_alarm_irq_enable(dev, alrm->enabled);
}