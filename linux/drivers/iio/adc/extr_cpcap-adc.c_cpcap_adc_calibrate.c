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
struct cpcap_adc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPCAP_ADC_BATTI ; 
 int /*<<< orphan*/  CPCAP_ADC_CHG_ISENSE ; 
 int /*<<< orphan*/  CPCAP_REG_ADCAL1 ; 
 int /*<<< orphan*/  CPCAP_REG_ADCAL2 ; 
 int /*<<< orphan*/  ST_ADC_CAL_BATTI_HIGH_THRESHOLD ; 
 int /*<<< orphan*/  ST_ADC_CAL_BATTI_LOW_THRESHOLD ; 
 int /*<<< orphan*/  ST_ADC_CAL_CHRGI_HIGH_THRESHOLD ; 
 int /*<<< orphan*/  ST_ADC_CAL_CHRGI_LOW_THRESHOLD ; 
 int cpcap_adc_calibrate_one (struct cpcap_adc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cpcap_adc_calibrate(struct cpcap_adc *ddata)
{
	int error;

	error = cpcap_adc_calibrate_one(ddata, CPCAP_ADC_CHG_ISENSE,
					CPCAP_REG_ADCAL1,
					ST_ADC_CAL_CHRGI_LOW_THRESHOLD,
					ST_ADC_CAL_CHRGI_HIGH_THRESHOLD);
	if (error)
		return error;

	error = cpcap_adc_calibrate_one(ddata, CPCAP_ADC_BATTI,
					CPCAP_REG_ADCAL2,
					ST_ADC_CAL_BATTI_LOW_THRESHOLD,
					ST_ADC_CAL_BATTI_HIGH_THRESHOLD);
	if (error)
		return error;

	return 0;
}