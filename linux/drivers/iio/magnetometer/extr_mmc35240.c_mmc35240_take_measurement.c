#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mmc35240_data {TYPE_1__* client; int /*<<< orphan*/  regmap; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  MMC35240_CTRL0_TM_BIT ; 
 int /*<<< orphan*/  MMC35240_REG_CTRL0 ; 
 int /*<<< orphan*/  MMC35240_REG_STATUS ; 
 unsigned int MMC35240_STATUS_MEAS_DONE_BIT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int mmc35240_take_measurement(struct mmc35240_data *data)
{
	int ret, tries = 100;
	unsigned int reg_status;

	ret = regmap_write(data->regmap, MMC35240_REG_CTRL0,
			   MMC35240_CTRL0_TM_BIT);
	if (ret < 0)
		return ret;

	while (tries-- > 0) {
		ret = regmap_read(data->regmap, MMC35240_REG_STATUS,
				  &reg_status);
		if (ret < 0)
			return ret;
		if (reg_status & MMC35240_STATUS_MEAS_DONE_BIT)
			break;
		/* minimum wait time to complete measurement is 10 ms */
		usleep_range(10000, 11000);
	}

	if (tries < 0) {
		dev_err(&data->client->dev, "data not ready\n");
		return -EIO;
	}

	return 0;
}