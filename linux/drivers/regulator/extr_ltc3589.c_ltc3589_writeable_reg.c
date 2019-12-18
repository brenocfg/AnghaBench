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
#define  LTC3589_B1DTV1 142 
#define  LTC3589_B1DTV2 141 
#define  LTC3589_B2DTV1 140 
#define  LTC3589_B2DTV2 139 
#define  LTC3589_B3DTV1 138 
#define  LTC3589_B3DTV2 137 
#define  LTC3589_CLIRQ 136 
#define  LTC3589_IRQSTAT 135 
#define  LTC3589_L2DTV1 134 
#define  LTC3589_L2DTV2 133 
#define  LTC3589_OVEN 132 
#define  LTC3589_SCR1 131 
#define  LTC3589_SCR2 130 
#define  LTC3589_VCCR 129 
#define  LTC3589_VRRCR 128 

__attribute__((used)) static bool ltc3589_writeable_reg(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case LTC3589_IRQSTAT:
	case LTC3589_SCR1:
	case LTC3589_OVEN:
	case LTC3589_SCR2:
	case LTC3589_VCCR:
	case LTC3589_CLIRQ:
	case LTC3589_B1DTV1:
	case LTC3589_B1DTV2:
	case LTC3589_VRRCR:
	case LTC3589_B2DTV1:
	case LTC3589_B2DTV2:
	case LTC3589_B3DTV1:
	case LTC3589_B3DTV2:
	case LTC3589_L2DTV1:
	case LTC3589_L2DTV2:
		return true;
	}
	return false;
}