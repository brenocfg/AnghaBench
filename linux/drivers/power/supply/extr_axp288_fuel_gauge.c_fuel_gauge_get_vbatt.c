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
struct axp288_fg_info {int /*<<< orphan*/ * iio_channel; } ;

/* Variables and functions */
 size_t BAT_VOLT ; 
 int VOLTAGE_FROM_ADC (int) ; 
 int iio_read_channel_raw (int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int fuel_gauge_get_vbatt(struct axp288_fg_info *info, int *vbatt)
{
	int ret = 0, raw_val;

	ret = iio_read_channel_raw(info->iio_channel[BAT_VOLT], &raw_val);
	if (ret < 0)
		goto vbatt_read_fail;

	*vbatt = VOLTAGE_FROM_ADC(raw_val);
vbatt_read_fail:
	return ret;
}