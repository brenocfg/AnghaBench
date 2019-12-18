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
#define  LM3601X_FLAGS_REG 128 

__attribute__((used)) static bool lm3601x_volatile_reg(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case LM3601X_FLAGS_REG:
		return true;
	default:
		return false;
	}
}