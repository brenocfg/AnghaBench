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
typedef  int u8 ;
struct adc5_chip {int dummy; } ;
struct adc5_channel_prop {int cal_val; int cal_method; int decimation; } ;

/* Variables and functions */
 int ADC5_USR_DIG_PARAM_CAL_SEL ; 
 int ADC5_USR_DIG_PARAM_CAL_SEL_SHIFT ; 
 int ADC5_USR_DIG_PARAM_CAL_VAL ; 
 int ADC5_USR_DIG_PARAM_CAL_VAL_SHIFT ; 
 int ADC5_USR_DIG_PARAM_DEC_RATIO_SEL ; 
 int ADC5_USR_DIG_PARAM_DEC_RATIO_SEL_SHIFT ; 

__attribute__((used)) static void adc5_update_dig_param(struct adc5_chip *adc,
			struct adc5_channel_prop *prop, u8 *data)
{
	/* Update calibration value */
	*data &= ~ADC5_USR_DIG_PARAM_CAL_VAL;
	*data |= (prop->cal_val << ADC5_USR_DIG_PARAM_CAL_VAL_SHIFT);

	/* Update calibration select */
	*data &= ~ADC5_USR_DIG_PARAM_CAL_SEL;
	*data |= (prop->cal_method << ADC5_USR_DIG_PARAM_CAL_SEL_SHIFT);

	/* Update decimation ratio select */
	*data &= ~ADC5_USR_DIG_PARAM_DEC_RATIO_SEL;
	*data |= (prop->decimation << ADC5_USR_DIG_PARAM_DEC_RATIO_SEL_SHIFT);
}