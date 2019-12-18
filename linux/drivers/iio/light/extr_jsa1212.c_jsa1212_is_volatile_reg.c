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
#define  JSA1212_ALS_DT1_REG 131 
#define  JSA1212_ALS_DT2_REG 130 
#define  JSA1212_INT_REG 129 
#define  JSA1212_PXS_DATA_REG 128 

__attribute__((used)) static bool jsa1212_is_volatile_reg(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case JSA1212_PXS_DATA_REG:
	case JSA1212_ALS_DT1_REG:
	case JSA1212_ALS_DT2_REG:
	case JSA1212_INT_REG:
		return true;
	default:
		return false;
	}
}