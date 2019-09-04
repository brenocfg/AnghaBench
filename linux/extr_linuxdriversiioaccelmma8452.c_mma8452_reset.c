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
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  MMA8452_CTRL_REG2 ; 
 int MMA8452_CTRL_REG2_RST ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int mma8452_reset(struct i2c_client *client)
{
	int i;
	int ret;

	ret = i2c_smbus_write_byte_data(client,	MMA8452_CTRL_REG2,
					MMA8452_CTRL_REG2_RST);
	if (ret < 0)
		return ret;

	for (i = 0; i < 10; i++) {
		usleep_range(100, 200);
		ret = i2c_smbus_read_byte_data(client, MMA8452_CTRL_REG2);
		if (ret == -EIO)
			continue; /* I2C comm reset */
		if (ret < 0)
			return ret;
		if (!(ret & MMA8452_CTRL_REG2_RST))
			return 0;
	}

	return -ETIMEDOUT;
}