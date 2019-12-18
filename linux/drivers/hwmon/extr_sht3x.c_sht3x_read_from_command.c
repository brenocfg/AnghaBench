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
struct sht3x_data {int /*<<< orphan*/  i2c_lock; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int SHT3X_CMD_LENGTH ; 
 int i2c_master_recv (struct i2c_client*,char*,int) ; 
 int i2c_master_send (struct i2c_client*,char const*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usleep_range (scalar_t__,scalar_t__) ; 

__attribute__((used)) static int sht3x_read_from_command(struct i2c_client *client,
				   struct sht3x_data *data,
				   const char *command,
				   char *buf, int length, u32 wait_time)
{
	int ret;

	mutex_lock(&data->i2c_lock);
	ret = i2c_master_send(client, command, SHT3X_CMD_LENGTH);

	if (ret != SHT3X_CMD_LENGTH) {
		ret = ret < 0 ? ret : -EIO;
		goto out;
	}

	if (wait_time)
		usleep_range(wait_time, wait_time + 1000);

	ret = i2c_master_recv(client, buf, length);
	if (ret != length) {
		ret = ret < 0 ? ret : -EIO;
		goto out;
	}

	ret = 0;
out:
	mutex_unlock(&data->i2c_lock);
	return ret;
}