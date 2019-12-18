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
struct mma7455_data {int /*<<< orphan*/  regmap; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  MMA7455_REG_STATUS ; 
 unsigned int MMA7455_STATUS_DRDY ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 struct device* regmap_get_device (int /*<<< orphan*/ ) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static int mma7455_drdy(struct mma7455_data *mma7455)
{
	struct device *dev = regmap_get_device(mma7455->regmap);
	unsigned int reg;
	int tries = 3;
	int ret;

	while (tries-- > 0) {
		ret = regmap_read(mma7455->regmap, MMA7455_REG_STATUS, &reg);
		if (ret)
			return ret;

		if (reg & MMA7455_STATUS_DRDY)
			return 0;

		msleep(20);
	}

	dev_warn(dev, "data not ready\n");

	return -EIO;
}