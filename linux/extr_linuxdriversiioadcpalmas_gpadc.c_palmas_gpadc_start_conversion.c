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
struct palmas_gpadc {int /*<<< orphan*/  dev; int /*<<< orphan*/  palmas; int /*<<< orphan*/  conv_completion; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  PALMAS_ADC_CONVERSION_TIMEOUT ; 
 int /*<<< orphan*/  PALMAS_GPADC_BASE ; 
 int /*<<< orphan*/  PALMAS_GPADC_SW_CONV0_LSB ; 
 int /*<<< orphan*/  PALMAS_GPADC_SW_SELECT ; 
 int /*<<< orphan*/  PALMAS_GPADC_SW_SELECT_SW_START_CONV0 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int palmas_bulk_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*,int) ; 
 int palmas_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int palmas_gpadc_start_conversion(struct palmas_gpadc *adc, int adc_chan)
{
	unsigned int val;
	int ret;

	init_completion(&adc->conv_completion);
	ret = palmas_update_bits(adc->palmas, PALMAS_GPADC_BASE,
				PALMAS_GPADC_SW_SELECT,
				PALMAS_GPADC_SW_SELECT_SW_START_CONV0,
				PALMAS_GPADC_SW_SELECT_SW_START_CONV0);
	if (ret < 0) {
		dev_err(adc->dev, "SELECT_SW_START write failed: %d\n", ret);
		return ret;
	}

	ret = wait_for_completion_timeout(&adc->conv_completion,
				PALMAS_ADC_CONVERSION_TIMEOUT);
	if (ret == 0) {
		dev_err(adc->dev, "conversion not completed\n");
		return -ETIMEDOUT;
	}

	ret = palmas_bulk_read(adc->palmas, PALMAS_GPADC_BASE,
				PALMAS_GPADC_SW_CONV0_LSB, &val, 2);
	if (ret < 0) {
		dev_err(adc->dev, "SW_CONV0_LSB read failed: %d\n", ret);
		return ret;
	}

	ret = val & 0xFFF;

	return ret;
}