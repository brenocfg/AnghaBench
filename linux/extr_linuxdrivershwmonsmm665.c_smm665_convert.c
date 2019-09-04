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
typedef  int u16 ;

/* Variables and functions */
 int SMM665_12VIN_ADC_TO_VOLTS (int) ; 
 int SMM665_ADC_MASK ; 
 int SMM665_AIN_ADC_TO_VOLTS (int) ; 
#define  SMM665_MISC16_ADC_DATA_12V 138 
#define  SMM665_MISC16_ADC_DATA_A 137 
#define  SMM665_MISC16_ADC_DATA_AIN1 136 
#define  SMM665_MISC16_ADC_DATA_AIN2 135 
#define  SMM665_MISC16_ADC_DATA_B 134 
#define  SMM665_MISC16_ADC_DATA_C 133 
#define  SMM665_MISC16_ADC_DATA_D 132 
#define  SMM665_MISC16_ADC_DATA_E 131 
#define  SMM665_MISC16_ADC_DATA_F 130 
#define  SMM665_MISC16_ADC_DATA_INT_TEMP 129 
#define  SMM665_MISC16_ADC_DATA_VDD 128 
 int SMM665_TEMP_ADC_TO_CELSIUS (int) ; 
 int SMM665_VMON_ADC_TO_VOLTS (int) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 

__attribute__((used)) static int smm665_convert(u16 adcval, int index)
{
	int val = 0;

	switch (index) {
	case SMM665_MISC16_ADC_DATA_12V:
		val = SMM665_12VIN_ADC_TO_VOLTS(adcval & SMM665_ADC_MASK);
		break;

	case SMM665_MISC16_ADC_DATA_VDD:
	case SMM665_MISC16_ADC_DATA_A:
	case SMM665_MISC16_ADC_DATA_B:
	case SMM665_MISC16_ADC_DATA_C:
	case SMM665_MISC16_ADC_DATA_D:
	case SMM665_MISC16_ADC_DATA_E:
	case SMM665_MISC16_ADC_DATA_F:
		val = SMM665_VMON_ADC_TO_VOLTS(adcval & SMM665_ADC_MASK);
		break;

	case SMM665_MISC16_ADC_DATA_AIN1:
	case SMM665_MISC16_ADC_DATA_AIN2:
		val = SMM665_AIN_ADC_TO_VOLTS(adcval & SMM665_ADC_MASK);
		break;

	case SMM665_MISC16_ADC_DATA_INT_TEMP:
		val = SMM665_TEMP_ADC_TO_CELSIUS(adcval & SMM665_ADC_MASK);
		break;

	default:
		/* If we get here, the developer messed up */
		WARN_ON_ONCE(1);
		break;
	}

	return val;
}