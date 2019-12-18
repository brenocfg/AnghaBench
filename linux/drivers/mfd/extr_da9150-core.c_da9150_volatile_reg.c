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
#define  DA9150_ADETD_STAT 178 
#define  DA9150_ADETVB_CFG_C 177 
#define  DA9150_ADET_CMPSTAT 176 
#define  DA9150_ADET_CTRL_A 175 
#define  DA9150_CC_IAVG_RES_A 174 
#define  DA9150_CC_IAVG_RES_B 173 
#define  DA9150_CC_ICHG_RES_A 172 
#define  DA9150_CC_ICHG_RES_B 171 
#define  DA9150_CONTROL_B 170 
#define  DA9150_CONTROL_C 169 
#define  DA9150_CORE2WIRE_STAT_A 168 
#define  DA9150_COREBTLD_STAT_A 167 
#define  DA9150_CORE_DATA_A 166 
#define  DA9150_CORE_DATA_B 165 
#define  DA9150_CORE_DATA_C 164 
#define  DA9150_CORE_DATA_D 163 
#define  DA9150_EVENT_E 162 
#define  DA9150_EVENT_F 161 
#define  DA9150_EVENT_G 160 
#define  DA9150_EVENT_H 159 
#define  DA9150_FAULT_LOG_A 158 
#define  DA9150_FAULT_LOG_B 157 
#define  DA9150_FG_CTRL_B 156 
#define  DA9150_FW_CTRL_B 155 
#define  DA9150_FW_CTRL_C 154 
#define  DA9150_GPADC_CMAN 153 
#define  DA9150_GPADC_CRES_A 152 
#define  DA9150_GPADC_CRES_B 151 
#define  DA9150_GPADC_MAN 150 
#define  DA9150_GPADC_RES_A 149 
#define  DA9150_GPADC_RES_B 148 
#define  DA9150_PAGE_CON 147 
#define  DA9150_PPR_TCTR_B 146 
#define  DA9150_STATUS_A 145 
#define  DA9150_STATUS_B 144 
#define  DA9150_STATUS_C 143 
#define  DA9150_STATUS_D 142 
#define  DA9150_STATUS_E 141 
#define  DA9150_STATUS_F 140 
#define  DA9150_STATUS_G 139 
#define  DA9150_STATUS_H 138 
#define  DA9150_STATUS_I 137 
#define  DA9150_STATUS_J 136 
#define  DA9150_STATUS_K 135 
#define  DA9150_STATUS_L 134 
#define  DA9150_STATUS_N 133 
#define  DA9150_TAUX_CTRL_A 132 
#define  DA9150_TAUX_VALUE_H 131 
#define  DA9150_TAUX_VALUE_L 130 
#define  DA9150_TBAT_RES_A 129 
#define  DA9150_TBAT_RES_B 128 

__attribute__((used)) static bool da9150_volatile_reg(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case DA9150_PAGE_CON:
	case DA9150_STATUS_A:
	case DA9150_STATUS_B:
	case DA9150_STATUS_C:
	case DA9150_STATUS_D:
	case DA9150_STATUS_E:
	case DA9150_STATUS_F:
	case DA9150_STATUS_G:
	case DA9150_STATUS_H:
	case DA9150_STATUS_I:
	case DA9150_STATUS_J:
	case DA9150_STATUS_K:
	case DA9150_STATUS_L:
	case DA9150_STATUS_N:
	case DA9150_FAULT_LOG_A:
	case DA9150_FAULT_LOG_B:
	case DA9150_EVENT_E:
	case DA9150_EVENT_F:
	case DA9150_EVENT_G:
	case DA9150_EVENT_H:
	case DA9150_CONTROL_B:
	case DA9150_CONTROL_C:
	case DA9150_GPADC_MAN:
	case DA9150_GPADC_RES_A:
	case DA9150_GPADC_RES_B:
	case DA9150_ADETVB_CFG_C:
	case DA9150_ADETD_STAT:
	case DA9150_ADET_CMPSTAT:
	case DA9150_ADET_CTRL_A:
	case DA9150_PPR_TCTR_B:
	case DA9150_COREBTLD_STAT_A:
	case DA9150_CORE_DATA_A:
	case DA9150_CORE_DATA_B:
	case DA9150_CORE_DATA_C:
	case DA9150_CORE_DATA_D:
	case DA9150_CORE2WIRE_STAT_A:
	case DA9150_FW_CTRL_C:
	case DA9150_FG_CTRL_B:
	case DA9150_FW_CTRL_B:
	case DA9150_GPADC_CMAN:
	case DA9150_GPADC_CRES_A:
	case DA9150_GPADC_CRES_B:
	case DA9150_CC_ICHG_RES_A:
	case DA9150_CC_ICHG_RES_B:
	case DA9150_CC_IAVG_RES_A:
	case DA9150_CC_IAVG_RES_B:
	case DA9150_TAUX_CTRL_A:
	case DA9150_TAUX_VALUE_H:
	case DA9150_TAUX_VALUE_L:
	case DA9150_TBAT_RES_A:
	case DA9150_TBAT_RES_B:
		return true;
	default:
		return false;
	}
}