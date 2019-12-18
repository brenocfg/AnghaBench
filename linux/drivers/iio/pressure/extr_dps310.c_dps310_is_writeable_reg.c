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
#define  DPS310_CFG_REG 132 
#define  DPS310_MEAS_CFG 131 
#define  DPS310_PRS_CFG 130 
#define  DPS310_RESET 129 
#define  DPS310_TMP_CFG 128 

__attribute__((used)) static bool dps310_is_writeable_reg(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case DPS310_PRS_CFG:
	case DPS310_TMP_CFG:
	case DPS310_MEAS_CFG:
	case DPS310_CFG_REG:
	case DPS310_RESET:
	/* No documentation available on the registers below */
	case 0x0e:
	case 0x0f:
	case 0x62:
		return true;
	default:
		return false;
	}
}