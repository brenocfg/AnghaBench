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
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ SNVS_LPCR ; 
 int SNVS_LPCR_LPTA_EN ; 
 int SNVS_LPCR_LPWUI_EN ; 
 struct snvs_rtc_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,scalar_t__,int,int) ; 
 int rtc_write_sync_lp (struct snvs_rtc_data*) ; 

__attribute__((used)) static int snvs_rtc_alarm_irq_enable(struct device *dev, unsigned int enable)
{
	struct snvs_rtc_data *data = dev_get_drvdata(dev);

	regmap_update_bits(data->regmap, data->offset + SNVS_LPCR,
			   (SNVS_LPCR_LPTA_EN | SNVS_LPCR_LPWUI_EN),
			   enable ? (SNVS_LPCR_LPTA_EN | SNVS_LPCR_LPWUI_EN) : 0);

	return rtc_write_sync_lp(data);
}