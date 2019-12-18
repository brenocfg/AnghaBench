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
#define  DPS310_MEAS_CFG 134 
#define  DPS310_PRS_B0 133 
#define  DPS310_PRS_B1 132 
#define  DPS310_PRS_B2 131 
#define  DPS310_TMP_B0 130 
#define  DPS310_TMP_B1 129 
#define  DPS310_TMP_B2 128 

__attribute__((used)) static bool dps310_is_volatile_reg(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case DPS310_PRS_B0:
	case DPS310_PRS_B1:
	case DPS310_PRS_B2:
	case DPS310_TMP_B0:
	case DPS310_TMP_B1:
	case DPS310_TMP_B2:
	case DPS310_MEAS_CFG:
	case 0x32:	/* No documentation available on this register */
		return true;
	default:
		return false;
	}
}