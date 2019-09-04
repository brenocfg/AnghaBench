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
typedef  int u8 ;
struct regmap {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ regmap_bulk_read (struct regmap*,int,int*,int) ; 

__attribute__((used)) static int chtdc_ti_pmic_get_raw_temp(struct regmap *regmap, int reg)
{
	u8 buf[2];

	if (regmap_bulk_read(regmap, reg, buf, 2))
		return -EIO;

	/* stored in big-endian */
	return ((buf[0] & 0x03) << 8) | buf[1];
}