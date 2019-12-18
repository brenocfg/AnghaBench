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
#define  TWL6040_REG_ASICID 133 
#define  TWL6040_REG_ASICREV 132 
#define  TWL6040_REG_HPPLLCTL 131 
#define  TWL6040_REG_INTID 130 
#define  TWL6040_REG_LPPLLCTL 129 
#define  TWL6040_REG_STATUS 128 

__attribute__((used)) static bool twl6040_volatile_reg(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case TWL6040_REG_ASICID:
	case TWL6040_REG_ASICREV:
	case TWL6040_REG_INTID:
	case TWL6040_REG_LPPLLCTL:
	case TWL6040_REG_HPPLLCTL:
	case TWL6040_REG_STATUS:
		return true;
	default:
		return false;
	}
}