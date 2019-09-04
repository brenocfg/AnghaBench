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
typedef  int u8 ;
struct ab8500_gpadc {int /*<<< orphan*/  dev; TYPE_1__* cal_data; } ;
struct TYPE_2__ {int gain; int /*<<< orphan*/  offset; } ;

/* Variables and functions */
#define  ACC_DETECT1 143 
#define  ACC_DETECT2 142 
#define  ADC_AUX1 141 
#define  ADC_AUX2 140 
 int ADC_CH_ACCDET2_MAX ; 
 int ADC_CH_ACCDET2_MIN ; 
 int ADC_CH_BKBAT_MAX ; 
 int ADC_CH_BKBAT_MIN ; 
 int ADC_CH_BTEMP_MAX ; 
 int ADC_CH_BTEMP_MIN ; 
 int ADC_CH_CHG_I_MAX ; 
 int ADC_CH_CHG_I_MIN ; 
 int ADC_CH_CHG_V_MAX ; 
 int ADC_CH_CHG_V_MIN ; 
 int ADC_CH_DIETEMP_MAX ; 
 int ADC_CH_DIETEMP_MIN ; 
 int ADC_CH_IBAT_MAX ; 
 int ADC_CH_IBAT_MIN ; 
 int ADC_CH_VBAT_MAX ; 
 int ADC_CH_VBAT_MIN ; 
 size_t ADC_INPUT_BTEMP ; 
 size_t ADC_INPUT_IBAT ; 
 size_t ADC_INPUT_VBAT ; 
 size_t ADC_INPUT_VMAIN ; 
 int ADC_RESOLUTION ; 
#define  BAT_CTRL 139 
#define  BK_BAT_V 138 
#define  BTEMP_BALL 137 
 int CALIB_SCALE ; 
 int CALIB_SHIFT_IBAT ; 
#define  DIE_TEMP 136 
 int EINVAL ; 
#define  IBAT_VIRTUAL_CHANNEL 135 
#define  MAIN_BAT_V 134 
#define  MAIN_CHARGER_C 133 
#define  MAIN_CHARGER_V 132 
#define  USB_CHARGER_C 131 
#define  VBAT_TRUE_MEAS 130 
#define  VBUS_V 129 
#define  XTAL_TEMP 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 

int ab8500_gpadc_ad_to_voltage(struct ab8500_gpadc *gpadc, u8 channel,
	int ad_value)
{
	int res;

	switch (channel) {
	case MAIN_CHARGER_V:
		/* For some reason we don't have calibrated data */
		if (!gpadc->cal_data[ADC_INPUT_VMAIN].gain) {
			res = ADC_CH_CHG_V_MIN + (ADC_CH_CHG_V_MAX -
				ADC_CH_CHG_V_MIN) * ad_value /
				ADC_RESOLUTION;
			break;
		}
		/* Here we can use the calibrated data */
		res = (int) (ad_value * gpadc->cal_data[ADC_INPUT_VMAIN].gain +
			gpadc->cal_data[ADC_INPUT_VMAIN].offset) / CALIB_SCALE;
		break;

	case XTAL_TEMP:
	case BAT_CTRL:
	case BTEMP_BALL:
	case ACC_DETECT1:
	case ADC_AUX1:
	case ADC_AUX2:
		/* For some reason we don't have calibrated data */
		if (!gpadc->cal_data[ADC_INPUT_BTEMP].gain) {
			res = ADC_CH_BTEMP_MIN + (ADC_CH_BTEMP_MAX -
				ADC_CH_BTEMP_MIN) * ad_value /
				ADC_RESOLUTION;
			break;
		}
		/* Here we can use the calibrated data */
		res = (int) (ad_value * gpadc->cal_data[ADC_INPUT_BTEMP].gain +
			gpadc->cal_data[ADC_INPUT_BTEMP].offset) / CALIB_SCALE;
		break;

	case MAIN_BAT_V:
	case VBAT_TRUE_MEAS:
		/* For some reason we don't have calibrated data */
		if (!gpadc->cal_data[ADC_INPUT_VBAT].gain) {
			res = ADC_CH_VBAT_MIN + (ADC_CH_VBAT_MAX -
				ADC_CH_VBAT_MIN) * ad_value /
				ADC_RESOLUTION;
			break;
		}
		/* Here we can use the calibrated data */
		res = (int) (ad_value * gpadc->cal_data[ADC_INPUT_VBAT].gain +
			gpadc->cal_data[ADC_INPUT_VBAT].offset) / CALIB_SCALE;
		break;

	case DIE_TEMP:
		res = ADC_CH_DIETEMP_MIN +
			(ADC_CH_DIETEMP_MAX - ADC_CH_DIETEMP_MIN) * ad_value /
			ADC_RESOLUTION;
		break;

	case ACC_DETECT2:
		res = ADC_CH_ACCDET2_MIN +
			(ADC_CH_ACCDET2_MAX - ADC_CH_ACCDET2_MIN) * ad_value /
			ADC_RESOLUTION;
		break;

	case VBUS_V:
		res = ADC_CH_CHG_V_MIN +
			(ADC_CH_CHG_V_MAX - ADC_CH_CHG_V_MIN) * ad_value /
			ADC_RESOLUTION;
		break;

	case MAIN_CHARGER_C:
	case USB_CHARGER_C:
		res = ADC_CH_CHG_I_MIN +
			(ADC_CH_CHG_I_MAX - ADC_CH_CHG_I_MIN) * ad_value /
			ADC_RESOLUTION;
		break;

	case BK_BAT_V:
		res = ADC_CH_BKBAT_MIN +
			(ADC_CH_BKBAT_MAX - ADC_CH_BKBAT_MIN) * ad_value /
			ADC_RESOLUTION;
		break;

	case IBAT_VIRTUAL_CHANNEL:
		/* For some reason we don't have calibrated data */
		if (!gpadc->cal_data[ADC_INPUT_IBAT].gain) {
			res = ADC_CH_IBAT_MIN + (ADC_CH_IBAT_MAX -
				ADC_CH_IBAT_MIN) * ad_value /
				ADC_RESOLUTION;
			break;
		}
		/* Here we can use the calibrated data */
		res = (int) (ad_value * gpadc->cal_data[ADC_INPUT_IBAT].gain +
				gpadc->cal_data[ADC_INPUT_IBAT].offset)
				>> CALIB_SHIFT_IBAT;
		break;

	default:
		dev_err(gpadc->dev,
			"unknown channel, not possible to convert\n");
		res = -EINVAL;
		break;

	}
	return res;
}