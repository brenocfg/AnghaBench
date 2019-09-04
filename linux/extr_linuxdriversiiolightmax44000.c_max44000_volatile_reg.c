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
#define  MAX44000_REG_ALS_DATA_HI 131 
#define  MAX44000_REG_ALS_DATA_LO 130 
#define  MAX44000_REG_PRX_DATA 129 
#define  MAX44000_REG_STATUS 128 

__attribute__((used)) static bool max44000_volatile_reg(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case MAX44000_REG_STATUS:
	case MAX44000_REG_ALS_DATA_HI:
	case MAX44000_REG_ALS_DATA_LO:
	case MAX44000_REG_PRX_DATA:
		return true;
	default:
		return false;
	}
}