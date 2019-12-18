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
#define  MXC6255_REG_CHIP_ID 130 
#define  MXC6255_REG_XOUT 129 
#define  MXC6255_REG_YOUT 128 

__attribute__((used)) static bool mxc6255_is_readable_reg(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case MXC6255_REG_XOUT:
	case MXC6255_REG_YOUT:
	case MXC6255_REG_CHIP_ID:
		return true;
	default:
		return false;
	}
}