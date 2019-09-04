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
struct regmap {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ regmap_read (struct regmap*,int,int*) ; 

__attribute__((used)) static int intel_crc_pmic_get_raw_temp(struct regmap *regmap, int reg)
{
	int temp_l, temp_h;

	/*
	 * Raw temperature value is 10bits: 8bits in reg
	 * and 2bits in reg-1: bit0,1
	 */
	if (regmap_read(regmap, reg, &temp_l) ||
	    regmap_read(regmap, reg - 1, &temp_h))
		return -EIO;

	return temp_l | (temp_h & 0x3) << 8;
}