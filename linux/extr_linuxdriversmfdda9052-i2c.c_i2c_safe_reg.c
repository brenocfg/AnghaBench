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

/* Variables and functions */
#define  DA9052_ADCIN4_RES_REG 144 
#define  DA9052_ADCIN5_RES_REG 143 
#define  DA9052_ADCIN6_RES_REG 142 
#define  DA9052_ADC_RES_H_REG 141 
#define  DA9052_ADC_RES_L_REG 140 
#define  DA9052_ICHG_AV_REG 139 
#define  DA9052_STATUS_A_REG 138 
#define  DA9052_STATUS_B_REG 137 
#define  DA9052_STATUS_C_REG 136 
#define  DA9052_STATUS_D_REG 135 
#define  DA9052_TBAT_RES_REG 134 
#define  DA9052_TJUNC_RES_REG 133 
#define  DA9052_TSI_LSB_REG 132 
#define  DA9052_TSI_X_MSB_REG 131 
#define  DA9052_TSI_Y_MSB_REG 130 
#define  DA9052_TSI_Z_MSB_REG 129 
#define  DA9052_VDD_RES_REG 128 

__attribute__((used)) static inline bool i2c_safe_reg(unsigned char reg)
{
	switch (reg) {
	case DA9052_STATUS_A_REG:
	case DA9052_STATUS_B_REG:
	case DA9052_STATUS_C_REG:
	case DA9052_STATUS_D_REG:
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
		return true;
	default:
		return false;
	}
}