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
typedef  scalar_t__ u32 ;
struct mc13xxx {int /*<<< orphan*/  regmap; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ BIT (int) ; 
 int EINVAL ; 
 int /*<<< orphan*/  dev_vdbg (int /*<<< orphan*/ ,char*,unsigned int,scalar_t__) ; 
 int regmap_write (int /*<<< orphan*/ ,unsigned int,scalar_t__) ; 

int mc13xxx_reg_write(struct mc13xxx *mc13xxx, unsigned int offset, u32 val)
{
	dev_vdbg(mc13xxx->dev, "[0x%02x] <- 0x%06x\n", offset, val);

	if (val >= BIT(24))
		return -EINVAL;

	return regmap_write(mc13xxx->regmap, offset, val);
}