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
struct hmc5843_data {int /*<<< orphan*/  dev; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int EIO ; 
 unsigned int HMC5843_DATA_READY ; 
 int /*<<< orphan*/  HMC5843_STATUS_REG ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static int hmc5843_wait_measurement(struct hmc5843_data *data)
{
	int tries = 150;
	unsigned int val;
	int ret;

	while (tries-- > 0) {
		ret = regmap_read(data->regmap, HMC5843_STATUS_REG, &val);
		if (ret < 0)
			return ret;
		if (val & HMC5843_DATA_READY)
			break;
		msleep(20);
	}

	if (tries < 0) {
		dev_err(data->dev, "data not ready\n");
		return -EIO;
	}

	return 0;
}