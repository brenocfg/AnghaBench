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
typedef  int u8 ;
struct video_i2c_data {TYPE_1__* chip; struct i2c_client* client; } ;
struct i2c_msg {int len; char* buf; scalar_t__ flags; int /*<<< orphan*/  addr; } ;
struct i2c_client {int /*<<< orphan*/  adapter; int /*<<< orphan*/  addr; } ;
struct TYPE_2__ {int buffer_size; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ I2C_M_RD ; 
 int i2c_transfer (int /*<<< orphan*/ ,struct i2c_msg*,int) ; 

__attribute__((used)) static int amg88xx_xfer(struct video_i2c_data *data, char *buf)
{
	struct i2c_client *client = data->client;
	struct i2c_msg msg[2];
	u8 reg = 0x80;
	int ret;

	msg[0].addr = client->addr;
	msg[0].flags = 0;
	msg[0].len = 1;
	msg[0].buf  = (char *)&reg;

	msg[1].addr = client->addr;
	msg[1].flags = I2C_M_RD;
	msg[1].len = data->chip->buffer_size;
	msg[1].buf = (char *)buf;

	ret = i2c_transfer(client->adapter, msg, 2);

	return (ret == 2) ? 0 : -EIO;
}