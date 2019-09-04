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
typedef  scalar_t__ u8 ;
struct lp8788 {int /*<<< orphan*/  dev; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int regmap_read (int /*<<< orphan*/ ,scalar_t__,unsigned int*) ; 

int lp8788_read_byte(struct lp8788 *lp, u8 reg, u8 *data)
{
	int ret;
	unsigned int val;

	ret = regmap_read(lp->regmap, reg, &val);
	if (ret < 0) {
		dev_err(lp->dev, "failed to read 0x%.2x\n", reg);
		return ret;
	}

	*data = (u8)val;
	return 0;
}