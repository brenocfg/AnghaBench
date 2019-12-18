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
#define  NOA1305_REG_INTEGRATION_TIME 133 
#define  NOA1305_REG_INT_SELECT 132 
#define  NOA1305_REG_INT_THRESH_LSB 131 
#define  NOA1305_REG_INT_THRESH_MSB 130 
#define  NOA1305_REG_POWER_CONTROL 129 
#define  NOA1305_REG_RESET 128 

__attribute__((used)) static bool noa1305_writable_reg(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case NOA1305_REG_POWER_CONTROL:
	case NOA1305_REG_RESET:
	case NOA1305_REG_INTEGRATION_TIME:
	case NOA1305_REG_INT_SELECT:
	case NOA1305_REG_INT_THRESH_LSB:
	case NOA1305_REG_INT_THRESH_MSB:
		return true;
	default:
		return false;
	}
}