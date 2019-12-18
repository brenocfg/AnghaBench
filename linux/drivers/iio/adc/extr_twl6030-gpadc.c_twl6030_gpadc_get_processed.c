#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct twl6030_ideal_code {int dummy; } ;
struct twl6030_gpadc_data {int /*<<< orphan*/  dev; TYPE_1__* twl6030_cal_tbl; TYPE_2__* pdata; } ;
struct TYPE_4__ {int /*<<< orphan*/  nchannels; struct twl6030_ideal_code* ideal; } ;
struct TYPE_3__ {int gain; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int twl6030_gpadc_get_raw (struct twl6030_gpadc_data*,int,int*) ; 
 int twl6030_gpadc_lookup (struct twl6030_ideal_code const*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int twl6030_gpadc_get_processed(struct twl6030_gpadc_data *gpadc,
		int channel, int *val)
{
	const struct twl6030_ideal_code *ideal = gpadc->pdata->ideal;
	int corrected_code;
	int channel_value;
	int i;
	int ret;

	ret = twl6030_gpadc_get_raw(gpadc, channel, &corrected_code);
	if (ret)
		return ret;

	i = twl6030_gpadc_lookup(ideal, channel, gpadc->pdata->nchannels);
	channel_value = corrected_code *
			gpadc->twl6030_cal_tbl[i].gain;

	/* Shift back into mV range */
	channel_value /= 1000;

	dev_dbg(gpadc->dev, "GPADC corrected code: %d", corrected_code);
	dev_dbg(gpadc->dev, "GPADC value: %d", channel_value);

	*val = channel_value;

	return ret;
}