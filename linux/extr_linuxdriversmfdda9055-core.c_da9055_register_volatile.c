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
#define  DA9055_REG_ADCIN1_RES 156 
#define  DA9055_REG_ADCIN2_RES 155 
#define  DA9055_REG_ADCIN3_RES 154 
#define  DA9055_REG_ADC_MAN 153 
#define  DA9055_REG_ADC_RES_H 152 
#define  DA9055_REG_ADC_RES_L 151 
#define  DA9055_REG_ALARM_MI 150 
#define  DA9055_REG_BCORE_CONT 149 
#define  DA9055_REG_BMEM_CONT 148 
#define  DA9055_REG_CONTROL_A 147 
#define  DA9055_REG_CONTROL_E 146 
#define  DA9055_REG_COUNT_D 145 
#define  DA9055_REG_COUNT_H 144 
#define  DA9055_REG_COUNT_MI 143 
#define  DA9055_REG_COUNT_MO 142 
#define  DA9055_REG_COUNT_S 141 
#define  DA9055_REG_COUNT_Y 140 
#define  DA9055_REG_EVENT_A 139 
#define  DA9055_REG_EVENT_B 138 
#define  DA9055_REG_EVENT_C 137 
#define  DA9055_REG_LDO1_CONT 136 
#define  DA9055_REG_LDO2_CONT 135 
#define  DA9055_REG_LDO3_CONT 134 
#define  DA9055_REG_LDO4_CONT 133 
#define  DA9055_REG_LDO5_CONT 132 
#define  DA9055_REG_LDO6_CONT 131 
#define  DA9055_REG_STATUS_A 130 
#define  DA9055_REG_STATUS_B 129 
#define  DA9055_REG_VSYS_RES 128 

__attribute__((used)) static bool da9055_register_volatile(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case DA9055_REG_STATUS_A:
	case DA9055_REG_STATUS_B:
	case DA9055_REG_EVENT_A:
	case DA9055_REG_EVENT_B:
	case DA9055_REG_EVENT_C:

	case DA9055_REG_CONTROL_A:
	case DA9055_REG_CONTROL_E:

	case DA9055_REG_ADC_MAN:
	case DA9055_REG_ADC_RES_L:
	case DA9055_REG_ADC_RES_H:
	case DA9055_REG_VSYS_RES:
	case DA9055_REG_ADCIN1_RES:
	case DA9055_REG_ADCIN2_RES:
	case DA9055_REG_ADCIN3_RES:

	case DA9055_REG_COUNT_S:
	case DA9055_REG_COUNT_MI:
	case DA9055_REG_COUNT_H:
	case DA9055_REG_COUNT_D:
	case DA9055_REG_COUNT_MO:
	case DA9055_REG_COUNT_Y:
	case DA9055_REG_ALARM_MI:

	case DA9055_REG_BCORE_CONT:
	case DA9055_REG_BMEM_CONT:
	case DA9055_REG_LDO1_CONT:
	case DA9055_REG_LDO2_CONT:
	case DA9055_REG_LDO3_CONT:
	case DA9055_REG_LDO4_CONT:
	case DA9055_REG_LDO5_CONT:
	case DA9055_REG_LDO6_CONT:
		return true;
	default:
		return false;
	}
}