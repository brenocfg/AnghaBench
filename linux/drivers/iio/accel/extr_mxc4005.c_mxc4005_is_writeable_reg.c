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
#define  MXC4005_REG_CONTROL 130 
#define  MXC4005_REG_INT_CLR1 129 
#define  MXC4005_REG_INT_MASK1 128 

__attribute__((used)) static bool mxc4005_is_writeable_reg(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case MXC4005_REG_INT_CLR1:
	case MXC4005_REG_INT_MASK1:
	case MXC4005_REG_CONTROL:
		return true;
	default:
		return false;
	}
}