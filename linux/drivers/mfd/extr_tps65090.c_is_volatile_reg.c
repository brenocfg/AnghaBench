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
#define  TPS65090_REG_CG_CTRL0 135 
#define  TPS65090_REG_CG_CTRL1 134 
#define  TPS65090_REG_CG_CTRL2 133 
#define  TPS65090_REG_CG_CTRL3 132 
#define  TPS65090_REG_CG_CTRL4 131 
#define  TPS65090_REG_CG_CTRL5 130 
#define  TPS65090_REG_INTR_MASK 129 
#define  TPS65090_REG_INTR_MASK2 128 

__attribute__((used)) static bool is_volatile_reg(struct device *dev, unsigned int reg)
{
	/* Nearly all registers have status bits mixed in, except a few */
	switch (reg) {
	case TPS65090_REG_INTR_MASK:
	case TPS65090_REG_INTR_MASK2:
	case TPS65090_REG_CG_CTRL0:
	case TPS65090_REG_CG_CTRL1:
	case TPS65090_REG_CG_CTRL2:
	case TPS65090_REG_CG_CTRL3:
	case TPS65090_REG_CG_CTRL4:
	case TPS65090_REG_CG_CTRL5:
		return false;
	}
	return true;
}