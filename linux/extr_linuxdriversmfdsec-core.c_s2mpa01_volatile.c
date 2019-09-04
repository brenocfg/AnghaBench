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
#define  S2MPA01_REG_INT1M 130 
#define  S2MPA01_REG_INT2M 129 
#define  S2MPA01_REG_INT3M 128 

__attribute__((used)) static bool s2mpa01_volatile(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case S2MPA01_REG_INT1M:
	case S2MPA01_REG_INT2M:
	case S2MPA01_REG_INT3M:
		return false;
	default:
		return true;
	}
}