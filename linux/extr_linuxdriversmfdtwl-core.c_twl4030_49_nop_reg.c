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

__attribute__((used)) static bool twl4030_49_nop_reg(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case 0x00:
	case 0x03:
	case 0x40:
	case 0x41:
	case 0x42:
		return false;
	default:
		return true;
	}
}