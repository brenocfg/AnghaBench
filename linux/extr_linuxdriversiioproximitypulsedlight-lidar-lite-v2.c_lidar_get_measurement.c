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
typedef  scalar_t__ u16 ;
struct lidar_data {struct i2c_client* client; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  LIDAR_REG_CONTROL_ACQUIRE ; 
 int /*<<< orphan*/  LIDAR_REG_STATUS ; 
 int LIDAR_REG_STATUS_INVALID ; 
 int LIDAR_REG_STATUS_READY ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int lidar_read_byte (struct lidar_data*,int /*<<< orphan*/ ) ; 
 int lidar_read_measurement (struct lidar_data*,scalar_t__*) ; 
 int lidar_write_control (struct lidar_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int lidar_get_measurement(struct lidar_data *data, u16 *reg)
{
	struct i2c_client *client = data->client;
	int tries = 10;
	int ret;

	pm_runtime_get_sync(&client->dev);

	/* start sample */
	ret = lidar_write_control(data, LIDAR_REG_CONTROL_ACQUIRE);
	if (ret < 0) {
		dev_err(&client->dev, "cannot send start measurement command");
		return ret;
	}

	while (tries--) {
		usleep_range(1000, 2000);

		ret = lidar_read_byte(data, LIDAR_REG_STATUS);
		if (ret < 0)
			break;

		/* return -EINVAL since laser is likely pointed out of range */
		if (ret & LIDAR_REG_STATUS_INVALID) {
			*reg = 0;
			ret = -EINVAL;
			break;
		}

		/* sample ready to read */
		if (!(ret & LIDAR_REG_STATUS_READY)) {
			ret = lidar_read_measurement(data, reg);
			break;
		}
		ret = -EIO;
	}
	pm_runtime_mark_last_busy(&client->dev);
	pm_runtime_put_autosuspend(&client->dev);

	return ret;
}