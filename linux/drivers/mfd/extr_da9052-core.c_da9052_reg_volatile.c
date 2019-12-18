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
struct device {int dummy; } ;

/* Variables and functions */
#define  DA9052_ADCIN4_RES_REG 160 
#define  DA9052_ADCIN5_RES_REG 159 
#define  DA9052_ADCIN6_RES_REG 158 
#define  DA9052_ADC_RES_H_REG 157 
#define  DA9052_ADC_RES_L_REG 156 
#define  DA9052_ALARM_MI_REG 155 
#define  DA9052_CHG_TIME_REG 154 
#define  DA9052_CONTROL_B_REG 153 
#define  DA9052_CONTROL_D_REG 152 
#define  DA9052_COUNT_D_REG 151 
#define  DA9052_COUNT_H_REG 150 
#define  DA9052_COUNT_MI_REG 149 
#define  DA9052_COUNT_MO_REG 148 
#define  DA9052_COUNT_S_REG 147 
#define  DA9052_COUNT_Y_REG 146 
#define  DA9052_EVENT_A_REG 145 
#define  DA9052_EVENT_B_REG 144 
#define  DA9052_EVENT_C_REG 143 
#define  DA9052_EVENT_D_REG 142 
#define  DA9052_FAULTLOG_REG 141 
#define  DA9052_ICHG_AV_REG 140 
#define  DA9052_STATUS_A_REG 139 
#define  DA9052_STATUS_B_REG 138 
#define  DA9052_STATUS_C_REG 137 
#define  DA9052_STATUS_D_REG 136 
#define  DA9052_SUPPLY_REG 135 
#define  DA9052_TBAT_RES_REG 134 
#define  DA9052_TJUNC_RES_REG 133 
#define  DA9052_TSI_LSB_REG 132 
#define  DA9052_TSI_X_MSB_REG 131 
#define  DA9052_TSI_Y_MSB_REG 130 
#define  DA9052_TSI_Z_MSB_REG 129 
#define  DA9052_VDD_RES_REG 128 

__attribute__((used)) static bool da9052_reg_volatile(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case DA9052_STATUS_A_REG:
	case DA9052_STATUS_B_REG:
	case DA9052_STATUS_C_REG:
	case DA9052_STATUS_D_REG:
	case DA9052_EVENT_A_REG:
	case DA9052_EVENT_B_REG:
	case DA9052_EVENT_C_REG:
	case DA9052_EVENT_D_REG:
	case DA9052_CONTROL_B_REG:
	case DA9052_CONTROL_D_REG:
	case DA9052_SUPPLY_REG:
	case DA9052_FAULTLOG_REG:
	case DA9052_CHG_TIME_REG:
	case DA9052_ADC_RES_L_REG:
	case DA9052_ADC_RES_H_REG:
	case DA9052_VDD_RES_REG:
	case DA9052_ICHG_AV_REG:
	case DA9052_TBAT_RES_REG:
	case DA9052_ADCIN4_RES_REG:
	case DA9052_ADCIN5_RES_REG:
	case DA9052_ADCIN6_RES_REG:
	case DA9052_TJUNC_RES_REG:
	case DA9052_TSI_X_MSB_REG:
	case DA9052_TSI_Y_MSB_REG:
	case DA9052_TSI_LSB_REG:
	case DA9052_TSI_Z_MSB_REG:
	case DA9052_COUNT_S_REG:
	case DA9052_COUNT_MI_REG:
	case DA9052_COUNT_H_REG:
	case DA9052_COUNT_D_REG:
	case DA9052_COUNT_MO_REG:
	case DA9052_COUNT_Y_REG:
	case DA9052_ALARM_MI_REG:
		return true;
	default:
		return false;
	}
}