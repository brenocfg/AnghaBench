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
typedef  int uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADC_MAX ; 
 int /*<<< orphan*/  ADC_MIN ; 
 int ADC_VAL0C ; 
 int ADC_VAL20C ; 
 int ADC_VAL40C ; 
 int ADC_VAL60C ; 
 int ERANGE ; 
 int /*<<< orphan*/  MSIC_DIE_ADC_MAX ; 
 int /*<<< orphan*/  MSIC_DIE_ADC_MIN ; 
 scalar_t__ is_valid_adc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int to_msic_die_temp (int) ; 

__attribute__((used)) static int adc_to_temp(int direct, uint16_t adc_val, int *tp)
{
	int temp;

	/* Direct conversion for die temperature */
	if (direct) {
		if (is_valid_adc(adc_val, MSIC_DIE_ADC_MIN, MSIC_DIE_ADC_MAX)) {
			*tp = to_msic_die_temp(adc_val) * 1000;
			return 0;
		}
		return -ERANGE;
	}

	if (!is_valid_adc(adc_val, ADC_MIN, ADC_MAX))
		return -ERANGE;

	/* Linear approximation for skin temperature */
	if (adc_val > ADC_VAL0C)
		temp = 177 - (adc_val/5);
	else if ((adc_val <= ADC_VAL0C) && (adc_val > ADC_VAL20C))
		temp = 111 - (adc_val/8);
	else if ((adc_val <= ADC_VAL20C) && (adc_val > ADC_VAL40C))
		temp = 92 - (adc_val/10);
	else if ((adc_val <= ADC_VAL40C) && (adc_val > ADC_VAL60C))
		temp = 91 - (adc_val/10);
	else
		temp = 112 - (adc_val/6);

	/* Convert temperature in celsius to milli degree celsius */
	*tp = temp * 1000;
	return 0;
}