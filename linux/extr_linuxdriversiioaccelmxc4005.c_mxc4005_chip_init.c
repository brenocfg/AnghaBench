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
struct mxc4005_data {int /*<<< orphan*/  dev; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  MXC4005_REG_DEVICE_ID ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static int mxc4005_chip_init(struct mxc4005_data *data)
{
	int ret;
	unsigned int reg;

	ret = regmap_read(data->regmap, MXC4005_REG_DEVICE_ID, &reg);
	if (ret < 0) {
		dev_err(data->dev, "failed to read chip id\n");
		return ret;
	}

	dev_dbg(data->dev, "MXC4005 chip id %02x\n", reg);

	return 0;
}