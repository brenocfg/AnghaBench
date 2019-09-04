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
#define  BMC150_MAGN_REG_INT_STATUS 136 
#define  BMC150_MAGN_REG_RHALL_L 135 
#define  BMC150_MAGN_REG_RHALL_M 134 
#define  BMC150_MAGN_REG_X_L 133 
#define  BMC150_MAGN_REG_X_M 132 
#define  BMC150_MAGN_REG_Y_L 131 
#define  BMC150_MAGN_REG_Y_M 130 
#define  BMC150_MAGN_REG_Z_L 129 
#define  BMC150_MAGN_REG_Z_M 128 

__attribute__((used)) static bool bmc150_magn_is_volatile_reg(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case BMC150_MAGN_REG_X_L:
	case BMC150_MAGN_REG_X_M:
	case BMC150_MAGN_REG_Y_L:
	case BMC150_MAGN_REG_Y_M:
	case BMC150_MAGN_REG_Z_L:
	case BMC150_MAGN_REG_Z_M:
	case BMC150_MAGN_REG_RHALL_L:
	case BMC150_MAGN_REG_RHALL_M:
	case BMC150_MAGN_REG_INT_STATUS:
		return true;
	default:
		return false;
	}
}