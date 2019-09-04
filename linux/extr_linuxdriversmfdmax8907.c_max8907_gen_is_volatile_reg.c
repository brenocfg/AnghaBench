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
#define  MAX8907_REG_CHG_IRQ1 133 
#define  MAX8907_REG_CHG_IRQ2 132 
#define  MAX8907_REG_CHG_STAT 131 
#define  MAX8907_REG_ON_OFF_IRQ1 130 
#define  MAX8907_REG_ON_OFF_IRQ2 129 
#define  MAX8907_REG_ON_OFF_STAT 128 

__attribute__((used)) static bool max8907_gen_is_volatile_reg(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case MAX8907_REG_ON_OFF_IRQ1:
	case MAX8907_REG_ON_OFF_STAT:
	case MAX8907_REG_ON_OFF_IRQ2:
	case MAX8907_REG_CHG_IRQ1:
	case MAX8907_REG_CHG_IRQ2:
	case MAX8907_REG_CHG_STAT:
		return true;
	default:
		return false;
	}
}