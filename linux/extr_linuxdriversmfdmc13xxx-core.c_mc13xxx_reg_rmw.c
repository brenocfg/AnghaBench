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
typedef  int u32 ;
struct mc13xxx {int /*<<< orphan*/  regmap; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  dev_vdbg (int /*<<< orphan*/ ,char*,unsigned int,int,int) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,unsigned int,int,int) ; 

int mc13xxx_reg_rmw(struct mc13xxx *mc13xxx, unsigned int offset,
		u32 mask, u32 val)
{
	BUG_ON(val & ~mask);
	dev_vdbg(mc13xxx->dev, "[0x%02x] <- 0x%06x (mask: 0x%06x)\n",
			offset, val, mask);

	return regmap_update_bits(mc13xxx->regmap, offset, mask, val);
}