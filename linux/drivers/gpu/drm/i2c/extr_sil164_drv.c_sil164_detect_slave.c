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
struct i2c_msg {int /*<<< orphan*/  len; int /*<<< orphan*/  addr; } ;
struct i2c_client {struct i2c_adapter* adapter; } ;
struct i2c_board_info {int /*<<< orphan*/  member_0; } ;
struct i2c_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  I2C_BOARD_INFO (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIL164_I2C_ADDR_SLAVE ; 
 struct i2c_client* i2c_new_device (struct i2c_adapter*,struct i2c_board_info const*) ; 
 int i2c_transfer (struct i2c_adapter*,struct i2c_msg*,int) ; 
 int /*<<< orphan*/  sil164_dbg (struct i2c_adapter*,char*) ; 

__attribute__((used)) static struct i2c_client *
sil164_detect_slave(struct i2c_client *client)
{
	struct i2c_adapter *adap = client->adapter;
	struct i2c_msg msg = {
		.addr = SIL164_I2C_ADDR_SLAVE,
		.len = 0,
	};
	const struct i2c_board_info info = {
		I2C_BOARD_INFO("sil164", SIL164_I2C_ADDR_SLAVE)
	};

	if (i2c_transfer(adap, &msg, 1) != 1) {
		sil164_dbg(adap, "No dual-link slave found.");
		return NULL;
	}

	return i2c_new_device(adap, &info);
}