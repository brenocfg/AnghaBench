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
typedef  int u8 ;
typedef  int u64 ;
struct i2c_msg {int flags; int len; int /*<<< orphan*/ * buf; int /*<<< orphan*/  addr; } ;
struct i2c_client {int flags; int /*<<< orphan*/  dev; int /*<<< orphan*/  adapter; int /*<<< orphan*/  addr; } ;
typedef  int /*<<< orphan*/  __u8 ;
typedef  scalar_t__ __be64 ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int ENODEV ; 
 int I2C_M_RD ; 
 int /*<<< orphan*/  MS_SENSORS_SERIAL_READ_LSB ; 
 int /*<<< orphan*/  MS_SENSORS_SERIAL_READ_MSB ; 
 int be64_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int i2c_transfer (int /*<<< orphan*/ ,struct i2c_msg*,int) ; 
 int /*<<< orphan*/  ms_sensors_crc_valid (int) ; 

int ms_sensors_read_serial(struct i2c_client *client, u64 *sn)
{
	u8 i;
	__be64 rcv_buf = 0;
	u64 rcv_val;
	__be16 send_buf;
	int ret;

	struct i2c_msg msg[2] = {
		{
		 .addr = client->addr,
		 .flags = client->flags,
		 .len = 2,
		 .buf = (__u8 *)&send_buf,
		 },
		{
		 .addr = client->addr,
		 .flags = client->flags | I2C_M_RD,
		 .buf = (__u8 *)&rcv_buf,
		 },
	};

	/* Read MSB part of serial number */
	send_buf = cpu_to_be16(MS_SENSORS_SERIAL_READ_MSB);
	msg[1].len = 8;
	ret = i2c_transfer(client->adapter, msg, 2);
	if (ret < 0) {
		dev_err(&client->dev, "Unable to read device serial number");
		return ret;
	}

	rcv_val = be64_to_cpu(rcv_buf);
	dev_dbg(&client->dev, "Serial MSB raw : %llx\n", rcv_val);

	for (i = 0; i < 64; i += 16) {
		if (!ms_sensors_crc_valid((rcv_val >> i) & 0xFFFF))
			return -ENODEV;
	}

	*sn = (((rcv_val >> 32) & 0xFF000000) |
	       ((rcv_val >> 24) & 0x00FF0000) |
	       ((rcv_val >> 16) & 0x0000FF00) |
	       ((rcv_val >> 8) & 0x000000FF)) << 16;

	/* Read LSB part of serial number */
	send_buf = cpu_to_be16(MS_SENSORS_SERIAL_READ_LSB);
	msg[1].len = 6;
	rcv_buf = 0;
	ret = i2c_transfer(client->adapter, msg, 2);
	if (ret < 0) {
		dev_err(&client->dev, "Unable to read device serial number");
		return ret;
	}

	rcv_val = be64_to_cpu(rcv_buf) >> 16;
	dev_dbg(&client->dev, "Serial MSB raw : %llx\n", rcv_val);

	for (i = 0; i < 48; i += 24) {
		if (!ms_sensors_crc_valid((rcv_val >> i) & 0xFFFFFF))
			return -ENODEV;
	}

	*sn |= (rcv_val & 0xFFFF00) << 40 | (rcv_val >> 32);

	return 0;
}