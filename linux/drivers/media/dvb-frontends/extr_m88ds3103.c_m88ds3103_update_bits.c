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
struct m88ds3103_dev {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int regmap_bulk_read (int /*<<< orphan*/ ,int,int*,int) ; 
 int regmap_bulk_write (int /*<<< orphan*/ ,int,int*,int) ; 

__attribute__((used)) static int m88ds3103_update_bits(struct m88ds3103_dev *dev,
				u8 reg, u8 mask, u8 val)
{
	int ret;
	u8 tmp;

	/* no need for read if whole reg is written */
	if (mask != 0xff) {
		ret = regmap_bulk_read(dev->regmap, reg, &tmp, 1);
		if (ret)
			return ret;

		val &= mask;
		tmp &= ~mask;
		val |= tmp;
	}

	return regmap_bulk_write(dev->regmap, reg, &val, 1);
}