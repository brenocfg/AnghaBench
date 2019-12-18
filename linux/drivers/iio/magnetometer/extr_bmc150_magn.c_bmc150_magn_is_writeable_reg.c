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
#define  BMC150_MAGN_REG_HIGH_THRESH 135 
#define  BMC150_MAGN_REG_INT 134 
#define  BMC150_MAGN_REG_INT_DRDY 133 
#define  BMC150_MAGN_REG_LOW_THRESH 132 
#define  BMC150_MAGN_REG_OPMODE_ODR 131 
#define  BMC150_MAGN_REG_POWER 130 
#define  BMC150_MAGN_REG_REP_XY 129 
#define  BMC150_MAGN_REG_REP_Z 128 

__attribute__((used)) static bool bmc150_magn_is_writeable_reg(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case BMC150_MAGN_REG_POWER:
	case BMC150_MAGN_REG_OPMODE_ODR:
	case BMC150_MAGN_REG_INT:
	case BMC150_MAGN_REG_INT_DRDY:
	case BMC150_MAGN_REG_LOW_THRESH:
	case BMC150_MAGN_REG_HIGH_THRESH:
	case BMC150_MAGN_REG_REP_XY:
	case BMC150_MAGN_REG_REP_Z:
		return true;
	default:
		return false;
	};
}