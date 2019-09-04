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
struct i2c_msg {int len; int* buf; int /*<<< orphan*/  flags; int /*<<< orphan*/  addr; } ;
struct i2c_client {int /*<<< orphan*/  dev; int /*<<< orphan*/  adapter; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
#define  I2C_MSP_CONTROL 129 
#define  I2C_MSP_DSP 128 
 int /*<<< orphan*/  I2C_M_IGNORE_NAK ; 
 int /*<<< orphan*/  I2C_M_RD ; 
 int /*<<< orphan*/  dev_dbg_lvl (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int i2c_transfer (int /*<<< orphan*/ ,struct i2c_msg*,int) ; 
 int /*<<< orphan*/  msp_debug ; 

int msp_reset(struct i2c_client *client)
{
	/* reset and read revision code */
	static u8 reset_off[3] = { I2C_MSP_CONTROL, 0x80, 0x00 };
	static u8 reset_on[3]  = { I2C_MSP_CONTROL, 0x00, 0x00 };
	static u8 write[3]     = { I2C_MSP_DSP + 1, 0x00, 0x1e };
	u8 read[2];
	struct i2c_msg reset[2] = {
		{
			.addr = client->addr,
			.flags = I2C_M_IGNORE_NAK,
			.len = 3,
			.buf = reset_off
		},
		{
			.addr = client->addr,
			.flags = I2C_M_IGNORE_NAK,
			.len = 3,
			.buf = reset_on
		},
	};
	struct i2c_msg test[2] = {
		{
			.addr = client->addr,
			.len = 3,
			.buf = write
		},
		{
			.addr = client->addr,
			.flags = I2C_M_RD,
			.len = 2,
			.buf = read
		},
	};

	dev_dbg_lvl(&client->dev, 3, msp_debug, "msp_reset\n");
	if (i2c_transfer(client->adapter, &reset[0], 1) != 1 ||
	    i2c_transfer(client->adapter, &reset[1], 1) != 1 ||
	    i2c_transfer(client->adapter, test, 2) != 2) {
		dev_err(&client->dev, "chip reset failed\n");
		return -1;
	}
	return 0;
}