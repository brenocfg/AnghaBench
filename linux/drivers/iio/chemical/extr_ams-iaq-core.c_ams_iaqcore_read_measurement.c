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
struct i2c_msg {int flags; int len; char* buf; int /*<<< orphan*/  addr; } ;
struct i2c_client {int flags; int /*<<< orphan*/  adapter; int /*<<< orphan*/  addr; } ;
struct ams_iaqcore_data {int /*<<< orphan*/  buffer; struct i2c_client* client; } ;

/* Variables and functions */
 int AMS_IAQCORE_DATA_SIZE ; 
 int I2C_M_RD ; 
 int i2c_transfer (int /*<<< orphan*/ ,struct i2c_msg*,int) ; 

__attribute__((used)) static int ams_iaqcore_read_measurement(struct ams_iaqcore_data *data)
{
	struct i2c_client *client = data->client;
	int ret;

	struct i2c_msg msg = {
		.addr = client->addr,
		.flags = client->flags | I2C_M_RD,
		.len = AMS_IAQCORE_DATA_SIZE,
		.buf = (char *) &data->buffer,
	};

	ret = i2c_transfer(client->adapter, &msg, 1);

	return (ret == AMS_IAQCORE_DATA_SIZE) ? 0 : ret;
}