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
#define  SC16IS7XX_IIR_REG 134 
#define  SC16IS7XX_IOSTATE_REG 133 
#define  SC16IS7XX_LSR_REG 132 
#define  SC16IS7XX_MSR_REG 131 
 unsigned int SC16IS7XX_REG_SHIFT ; 
#define  SC16IS7XX_RHR_REG 130 
#define  SC16IS7XX_RXLVL_REG 129 
#define  SC16IS7XX_TXLVL_REG 128 

__attribute__((used)) static bool sc16is7xx_regmap_volatile(struct device *dev, unsigned int reg)
{
	switch (reg >> SC16IS7XX_REG_SHIFT) {
	case SC16IS7XX_RHR_REG:
	case SC16IS7XX_IIR_REG:
	case SC16IS7XX_LSR_REG:
	case SC16IS7XX_MSR_REG:
	case SC16IS7XX_TXLVL_REG:
	case SC16IS7XX_RXLVL_REG:
	case SC16IS7XX_IOSTATE_REG:
		return true;
	default:
		break;
	}

	return false;
}