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
#define  AS3711_ASIC_ID_1 160 
#define  AS3711_ASIC_ID_2 159 
#define  AS3711_CHARGER_STATUS_1 158 
#define  AS3711_CHARGER_STATUS_2 157 
#define  AS3711_CURR1_VALUE 156 
#define  AS3711_CURR2_VALUE 155 
#define  AS3711_CURR3_VALUE 154 
#define  AS3711_CURR_CONTROL 153 
#define  AS3711_GPIO_SIGNAL_IN 152 
#define  AS3711_GPIO_SIGNAL_OUT 151 
#define  AS3711_INTERRUPT_STATUS_1 150 
#define  AS3711_INTERRUPT_STATUS_2 149 
#define  AS3711_INTERRUPT_STATUS_3 148 
#define  AS3711_LDO_1_VOLTAGE 147 
#define  AS3711_LDO_2_VOLTAGE 146 
#define  AS3711_LDO_3_VOLTAGE 145 
#define  AS3711_LDO_4_VOLTAGE 144 
#define  AS3711_LDO_5_VOLTAGE 143 
#define  AS3711_LDO_6_VOLTAGE 142 
#define  AS3711_LDO_7_VOLTAGE 141 
#define  AS3711_LDO_8_VOLTAGE 140 
#define  AS3711_REG_STATUS 139 
#define  AS3711_SD_1_VOLTAGE 138 
#define  AS3711_SD_2_VOLTAGE 137 
#define  AS3711_SD_3_VOLTAGE 136 
#define  AS3711_SD_4_VOLTAGE 135 
#define  AS3711_SD_CONTROL 134 
#define  AS3711_SD_CONTROL_1 133 
#define  AS3711_SD_CONTROL_2 132 
#define  AS3711_STEPUP_CONTROL_1 131 
#define  AS3711_STEPUP_CONTROL_2 130 
#define  AS3711_STEPUP_CONTROL_4 129 
#define  AS3711_STEPUP_CONTROL_5 128 

__attribute__((used)) static bool as3711_readable_reg(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case AS3711_SD_1_VOLTAGE:
	case AS3711_SD_2_VOLTAGE:
	case AS3711_SD_3_VOLTAGE:
	case AS3711_SD_4_VOLTAGE:
	case AS3711_LDO_1_VOLTAGE:
	case AS3711_LDO_2_VOLTAGE:
	case AS3711_LDO_3_VOLTAGE:
	case AS3711_LDO_4_VOLTAGE:
	case AS3711_LDO_5_VOLTAGE:
	case AS3711_LDO_6_VOLTAGE:
	case AS3711_LDO_7_VOLTAGE:
	case AS3711_LDO_8_VOLTAGE:
	case AS3711_SD_CONTROL:
	case AS3711_GPIO_SIGNAL_OUT:
	case AS3711_GPIO_SIGNAL_IN:
	case AS3711_SD_CONTROL_1:
	case AS3711_SD_CONTROL_2:
	case AS3711_CURR_CONTROL:
	case AS3711_CURR1_VALUE:
	case AS3711_CURR2_VALUE:
	case AS3711_CURR3_VALUE:
	case AS3711_STEPUP_CONTROL_1:
	case AS3711_STEPUP_CONTROL_2:
	case AS3711_STEPUP_CONTROL_4:
	case AS3711_STEPUP_CONTROL_5:
	case AS3711_REG_STATUS:
	case AS3711_INTERRUPT_STATUS_1:
	case AS3711_INTERRUPT_STATUS_2:
	case AS3711_INTERRUPT_STATUS_3:
	case AS3711_CHARGER_STATUS_1:
	case AS3711_CHARGER_STATUS_2:
	case AS3711_ASIC_ID_1:
	case AS3711_ASIC_ID_2:
		return true;
	}
	return false;
}