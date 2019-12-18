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
#define  RPR0521_REG_ALS_CTRL 130 
#define  RPR0521_REG_MODE_CTRL 129 
#define  RPR0521_REG_PXS_CTRL 128 

__attribute__((used)) static bool rpr0521_is_volatile_reg(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case RPR0521_REG_MODE_CTRL:
	case RPR0521_REG_ALS_CTRL:
	case RPR0521_REG_PXS_CTRL:
		return false;
	default:
		return true;
	}
}