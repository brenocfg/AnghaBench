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
typedef  int /*<<< orphan*/  u8 ;
struct lidar_data {struct i2c_client* client; } ;
struct i2c_msg {int flags; int len; char* buf; int /*<<< orphan*/  addr; } ;
struct i2c_client {int flags; int /*<<< orphan*/  adapter; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int EIO ; 
 int I2C_M_RD ; 
 int I2C_M_STOP ; 
 int i2c_transfer (int /*<<< orphan*/ ,struct i2c_msg*,int) ; 

__attribute__((used)) static int lidar_i2c_xfer(struct lidar_data *data, u8 reg, u8 *val, int len)
{
	struct i2c_client *client = data->client;
	struct i2c_msg msg[2];
	int ret;

	msg[0].addr = client->addr;
	msg[0].flags = client->flags | I2C_M_STOP;
	msg[0].len = 1;
	msg[0].buf  = (char *) &reg;

	msg[1].addr = client->addr;
	msg[1].flags = client->flags | I2C_M_RD;
	msg[1].len = len;
	msg[1].buf = (char *) val;

	ret = i2c_transfer(client->adapter, msg, 2);

	return (ret == 2) ? 0 : -EIO;
}