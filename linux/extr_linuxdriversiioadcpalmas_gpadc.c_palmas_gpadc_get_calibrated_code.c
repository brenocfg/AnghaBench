#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct palmas_gpadc {TYPE_1__* adc_info; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int offset; int gain_error; int gain; int /*<<< orphan*/  is_uncalibrated; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int palmas_gpadc_get_calibrated_code(struct palmas_gpadc *adc,
						int adc_chan, int val)
{
	if (!adc->adc_info[adc_chan].is_uncalibrated)
		val  = (val*1000 - adc->adc_info[adc_chan].offset) /
					adc->adc_info[adc_chan].gain_error;

	if (val < 0) {
		dev_err(adc->dev, "Mismatch with calibration\n");
		return 0;
	}

	val = (val * adc->adc_info[adc_chan].gain) / 1000;

	return val;
}