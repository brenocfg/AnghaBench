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
typedef  int /*<<< orphan*/  u16 ;
struct cpcap_adc {scalar_t__ vendor; int /*<<< orphan*/  dev; int /*<<< orphan*/  reg; } ;
struct TYPE_2__ {short cal_offset; } ;

/* Variables and functions */
 int CPCAP_ADC_MAX_RETRIES ; 
 scalar_t__ CPCAP_VENDOR_TI ; 
 unsigned short ST_ADC_CALIBRATE_DIFF_THRESHOLD ; 
 TYPE_1__* bank_conversion ; 
 int /*<<< orphan*/  cpcap_adc_setup_calibrate (struct cpcap_adc*,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,short) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int cpcap_adc_calibrate_one(struct cpcap_adc *ddata,
				   int channel,
				   u16 calibration_register,
				   int lower_threshold,
				   int upper_threshold)
{
	unsigned int calibration_data[2];
	unsigned short cal_data_diff;
	int i, error;

	for (i = 0; i < CPCAP_ADC_MAX_RETRIES; i++) {
		calibration_data[0]  = 0;
		calibration_data[1]  = 0;
		cal_data_diff = 0;
		cpcap_adc_setup_calibrate(ddata, channel);
		error = regmap_read(ddata->reg, calibration_register,
				    &calibration_data[0]);
		if (error)
			return error;
		cpcap_adc_setup_calibrate(ddata, channel);
		error = regmap_read(ddata->reg, calibration_register,
				    &calibration_data[1]);
		if (error)
			return error;

		if (calibration_data[0] > calibration_data[1])
			cal_data_diff =
				calibration_data[0] - calibration_data[1];
		else
			cal_data_diff =
				calibration_data[1] - calibration_data[0];

		if (((calibration_data[1] >= lower_threshold) &&
		     (calibration_data[1] <= upper_threshold) &&
		     (cal_data_diff <= ST_ADC_CALIBRATE_DIFF_THRESHOLD)) ||
		    (ddata->vendor == CPCAP_VENDOR_TI)) {
			bank_conversion[channel].cal_offset =
				((short)calibration_data[1] * -1) + 512;
			dev_dbg(ddata->dev, "ch%i calibration complete: %i\n",
				channel, bank_conversion[channel].cal_offset);
			break;
		}
		usleep_range(5000, 10000);
	}

	return 0;
}