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
#define  STK3310_REG_ALS_DATA_LSB 132 
#define  STK3310_REG_ALS_DATA_MSB 131 
#define  STK3310_REG_FLAG 130 
#define  STK3310_REG_PS_DATA_LSB 129 
#define  STK3310_REG_PS_DATA_MSB 128 

__attribute__((used)) static bool stk3310_is_volatile_reg(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case STK3310_REG_ALS_DATA_MSB:
	case STK3310_REG_ALS_DATA_LSB:
	case STK3310_REG_PS_DATA_LSB:
	case STK3310_REG_PS_DATA_MSB:
	case STK3310_REG_FLAG:
		return true;
	default:
		return false;
	}
}