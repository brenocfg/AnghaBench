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
struct twl6030_ideal_code {int volt2; int volt1; int code2; int code1; } ;
struct twl6030_gpadc_data {int /*<<< orphan*/  dev; TYPE_2__* twl6030_cal_tbl; TYPE_1__* pdata; } ;
struct TYPE_4__ {int gain; int gain_error; int offset_error; } ;
struct TYPE_3__ {int /*<<< orphan*/  nchannels; struct twl6030_ideal_code* ideal; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int) ; 
 int twl6030_gpadc_lookup (struct twl6030_ideal_code const*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void twl6030_calibrate_channel(struct twl6030_gpadc_data *gpadc,
		int channel, int d1, int d2)
{
	int b, k, gain, x1, x2, i;
	const struct twl6030_ideal_code *ideal = gpadc->pdata->ideal;

	i = twl6030_gpadc_lookup(ideal, channel, gpadc->pdata->nchannels);

	/* Gain */
	gain = ((ideal[i].volt2 - ideal[i].volt1) * 1000) /
		(ideal[i].code2 - ideal[i].code1);

	x1 = ideal[i].code1;
	x2 = ideal[i].code2;

	/* k - real curve gain */
	k = 1000 + (((d2 - d1) * 1000) / (x2 - x1));

	/* b - offset of the real curve gain */
	b = (d1 * 1000) - (k - 1000) * x1;

	gpadc->twl6030_cal_tbl[i].gain = gain;
	gpadc->twl6030_cal_tbl[i].gain_error = k;
	gpadc->twl6030_cal_tbl[i].offset_error = b;

	dev_dbg(gpadc->dev, "GPADC d1   for Chn: %d = %d\n", channel, d1);
	dev_dbg(gpadc->dev, "GPADC d2   for Chn: %d = %d\n", channel, d2);
	dev_dbg(gpadc->dev, "GPADC x1   for Chn: %d = %d\n", channel, x1);
	dev_dbg(gpadc->dev, "GPADC x2   for Chn: %d = %d\n", channel, x2);
	dev_dbg(gpadc->dev, "GPADC Gain for Chn: %d = %d\n", channel, gain);
	dev_dbg(gpadc->dev, "GPADC k    for Chn: %d = %d\n", channel, k);
	dev_dbg(gpadc->dev, "GPADC b    for Chn: %d = %d\n", channel, b);
}