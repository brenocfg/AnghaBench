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
#define  GP2AP020A00F_D0_H_REG 134 
#define  GP2AP020A00F_D0_L_REG 133 
#define  GP2AP020A00F_D1_H_REG 132 
#define  GP2AP020A00F_D1_L_REG 131 
#define  GP2AP020A00F_D2_H_REG 130 
#define  GP2AP020A00F_D2_L_REG 129 
#define  GP2AP020A00F_OP_REG 128 

__attribute__((used)) static bool gp2ap020a00f_is_volatile_reg(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case GP2AP020A00F_OP_REG:
	case GP2AP020A00F_D0_L_REG:
	case GP2AP020A00F_D0_H_REG:
	case GP2AP020A00F_D1_L_REG:
	case GP2AP020A00F_D1_H_REG:
	case GP2AP020A00F_D2_L_REG:
	case GP2AP020A00F_D2_H_REG:
		return true;
	default:
		return false;
	}
}