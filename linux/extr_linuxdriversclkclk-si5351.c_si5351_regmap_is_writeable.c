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
 unsigned int SI5351_DEVICE_STATUS ; 

__attribute__((used)) static bool si5351_regmap_is_writeable(struct device *dev, unsigned int reg)
{
	/* reserved registers */
	if (reg >= 4 && reg <= 8)
		return false;
	if (reg >= 10 && reg <= 14)
		return false;
	if (reg >= 173 && reg <= 176)
		return false;
	if (reg >= 178 && reg <= 182)
		return false;
	/* read-only */
	if (reg == SI5351_DEVICE_STATUS)
		return false;
	return true;
}