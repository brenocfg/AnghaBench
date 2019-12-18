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
#define  ZPA2326_INT_SOURCE_REG 129 
#define  ZPA2326_PRESS_OUT_H_REG 128 

bool zpa2326_isreg_precious(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case ZPA2326_INT_SOURCE_REG:
	case ZPA2326_PRESS_OUT_H_REG:
		return true;

	default:
		return false;
	}
}