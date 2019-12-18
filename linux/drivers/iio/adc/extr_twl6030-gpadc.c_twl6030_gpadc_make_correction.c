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
struct twl6030_gpadc_data {TYPE_2__* twl6030_cal_tbl; TYPE_1__* pdata; } ;
struct TYPE_4__ {int offset_error; int gain_error; } ;
struct TYPE_3__ {int /*<<< orphan*/  nchannels; struct twl6030_ideal_code* ideal; } ;

/* Variables and functions */
 int twl6030_gpadc_lookup (struct twl6030_ideal_code const*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int twl6030_gpadc_make_correction(struct twl6030_gpadc_data *gpadc,
		int channel, int raw_code)
{
	const struct twl6030_ideal_code *ideal = gpadc->pdata->ideal;
	int corrected_code;
	int i;

	i = twl6030_gpadc_lookup(ideal, channel, gpadc->pdata->nchannels);
	corrected_code = ((raw_code * 1000) -
		gpadc->twl6030_cal_tbl[i].offset_error) /
		gpadc->twl6030_cal_tbl[i].gain_error;

	return corrected_code;
}