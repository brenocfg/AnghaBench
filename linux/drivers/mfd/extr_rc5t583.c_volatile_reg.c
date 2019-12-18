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
#define  RC5T583_GPIO_EN_INT 138 
#define  RC5T583_GPIO_GPEDGE1 137 
#define  RC5T583_GPIO_GPEDGE2 136 
 unsigned int RC5T583_GPIO_GPOFUNC ; 
 unsigned int RC5T583_GPIO_IOSEL ; 
#define  RC5T583_GPIO_MON_IOIN 135 
#define  RC5T583_INT_EN_ADC1 134 
#define  RC5T583_INT_EN_ADC2 133 
#define  RC5T583_INT_EN_ADC3 132 
#define  RC5T583_INT_EN_DCDC 131 
#define  RC5T583_INT_EN_RTC 130 
#define  RC5T583_INT_EN_SYS1 129 
#define  RC5T583_INT_EN_SYS2 128 
 unsigned int RC5T583_REG_DC0CTL ; 
 unsigned int RC5T583_REG_LDO9DAC_DS ; 
 unsigned int RC5T583_REG_LDOEN1 ; 
 unsigned int RC5T583_REG_SR3CTL ; 
 unsigned int RC5T583_SLPSEQ1 ; 
 unsigned int RC5T583_SLPSEQ11 ; 

__attribute__((used)) static bool volatile_reg(struct device *dev, unsigned int reg)
{
	/* Enable caching in interrupt registers */
	switch (reg) {
	case RC5T583_INT_EN_SYS1:
	case RC5T583_INT_EN_SYS2:
	case RC5T583_INT_EN_DCDC:
	case RC5T583_INT_EN_RTC:
	case RC5T583_INT_EN_ADC1:
	case RC5T583_INT_EN_ADC2:
	case RC5T583_INT_EN_ADC3:
	case RC5T583_GPIO_GPEDGE1:
	case RC5T583_GPIO_GPEDGE2:
	case RC5T583_GPIO_EN_INT:
		return false;

	case RC5T583_GPIO_MON_IOIN:
		/* This is gpio input register */
		return true;

	default:
		/* Enable caching in gpio registers */
		if ((reg >= RC5T583_GPIO_IOSEL) &&
				(reg <= RC5T583_GPIO_GPOFUNC))
			return false;

		/* Enable caching in sleep seq registers */
		if ((reg >= RC5T583_SLPSEQ1) && (reg <= RC5T583_SLPSEQ11))
			return false;

		/* Enable caching of regulator registers */
		if ((reg >= RC5T583_REG_DC0CTL) && (reg <= RC5T583_REG_SR3CTL))
			return false;
		if ((reg >= RC5T583_REG_LDOEN1) &&
					(reg <= RC5T583_REG_LDO9DAC_DS))
			return false;

		break;
	}

	return true;
}