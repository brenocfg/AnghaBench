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
struct palmas_gpadc {TYPE_1__* adc_info; int /*<<< orphan*/  dev; int /*<<< orphan*/  palmas; } ;
struct TYPE_2__ {int x1; int x2; int v1; int v2; int gain_error; int gain; int offset; int /*<<< orphan*/  trim2_reg; int /*<<< orphan*/  trim1_reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  PALMAS_TRIM_GPADC_BASE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int palmas_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int palmas_gpadc_calibrate(struct palmas_gpadc *adc, int adc_chan)
{
	int k;
	int d1;
	int d2;
	int ret;
	int gain;
	int x1 =  adc->adc_info[adc_chan].x1;
	int x2 =  adc->adc_info[adc_chan].x2;
	int v1 = adc->adc_info[adc_chan].v1;
	int v2 = adc->adc_info[adc_chan].v2;

	ret = palmas_read(adc->palmas, PALMAS_TRIM_GPADC_BASE,
				adc->adc_info[adc_chan].trim1_reg, &d1);
	if (ret < 0) {
		dev_err(adc->dev, "TRIM read failed: %d\n", ret);
		goto scrub;
	}

	ret = palmas_read(adc->palmas, PALMAS_TRIM_GPADC_BASE,
				adc->adc_info[adc_chan].trim2_reg, &d2);
	if (ret < 0) {
		dev_err(adc->dev, "TRIM read failed: %d\n", ret);
		goto scrub;
	}

	/* gain error calculation */
	k = (1000 + (1000 * (d2 - d1)) / (x2 - x1));

	/* gain calculation */
	gain = ((v2 - v1) * 1000) / (x2 - x1);

	adc->adc_info[adc_chan].gain_error = k;
	adc->adc_info[adc_chan].gain = gain;
	/* offset Calculation */
	adc->adc_info[adc_chan].offset = (d1 * 1000) - ((k - 1000) * x1);

scrub:
	return ret;
}