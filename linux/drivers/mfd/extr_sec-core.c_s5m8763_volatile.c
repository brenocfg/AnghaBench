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
#define  S5M8763_REG_IRQM1 131 
#define  S5M8763_REG_IRQM2 130 
#define  S5M8763_REG_IRQM3 129 
#define  S5M8763_REG_IRQM4 128 

__attribute__((used)) static bool s5m8763_volatile(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case S5M8763_REG_IRQM1:
	case S5M8763_REG_IRQM2:
	case S5M8763_REG_IRQM3:
	case S5M8763_REG_IRQM4:
		return false;
	default:
		return true;
	}
}