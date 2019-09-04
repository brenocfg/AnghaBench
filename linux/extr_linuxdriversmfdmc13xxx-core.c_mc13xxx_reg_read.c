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
typedef  int /*<<< orphan*/  u32 ;
struct mc13xxx {int /*<<< orphan*/  dev; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_vdbg (int /*<<< orphan*/ ,char*,unsigned int,int /*<<< orphan*/ ) ; 
 int regmap_read (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ *) ; 

int mc13xxx_reg_read(struct mc13xxx *mc13xxx, unsigned int offset, u32 *val)
{
	int ret;

	ret = regmap_read(mc13xxx->regmap, offset, val);
	dev_vdbg(mc13xxx->dev, "[0x%02x] -> 0x%06x\n", offset, *val);

	return ret;
}