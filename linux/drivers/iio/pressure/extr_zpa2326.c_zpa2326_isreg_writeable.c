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
#define  ZPA2326_CTRL_REG0_REG 137 
#define  ZPA2326_CTRL_REG1_REG 136 
#define  ZPA2326_CTRL_REG2_REG 135 
#define  ZPA2326_CTRL_REG3_REG 134 
#define  ZPA2326_REF_P_H_REG 133 
#define  ZPA2326_REF_P_L_REG 132 
#define  ZPA2326_REF_P_XL_REG 131 
#define  ZPA2326_RES_CONF_REG 130 
#define  ZPA2326_THS_P_HIGH_REG 129 
#define  ZPA2326_THS_P_LOW_REG 128 

bool zpa2326_isreg_writeable(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case ZPA2326_REF_P_XL_REG:
	case ZPA2326_REF_P_L_REG:
	case ZPA2326_REF_P_H_REG:
	case ZPA2326_RES_CONF_REG:
	case ZPA2326_CTRL_REG0_REG:
	case ZPA2326_CTRL_REG1_REG:
	case ZPA2326_CTRL_REG2_REG:
	case ZPA2326_CTRL_REG3_REG:
	case ZPA2326_THS_P_LOW_REG:
	case ZPA2326_THS_P_HIGH_REG:
		return true;

	default:
		return false;
	}
}