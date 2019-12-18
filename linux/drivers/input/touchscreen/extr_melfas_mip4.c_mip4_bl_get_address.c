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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct mip4_ts {TYPE_1__* client; } ;
struct i2c_msg {int len; int /*<<< orphan*/ * buf; int /*<<< orphan*/  flags; int /*<<< orphan*/  addr; } ;
typedef  int /*<<< orphan*/  result ;
typedef  int /*<<< orphan*/  cmd ;
struct TYPE_2__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  adapter; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct i2c_msg*) ; 
 int EIO ; 
 int /*<<< orphan*/  I2C_M_RD ; 
 int /*<<< orphan*/  MIP4_R0_BOOT ; 
 int /*<<< orphan*/  MIP4_R1_BOOT_BUF_ADDR ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  get_unaligned_le16 (int /*<<< orphan*/ *) ; 
 int i2c_transfer (int /*<<< orphan*/ ,struct i2c_msg*,int) ; 

__attribute__((used)) static int mip4_bl_get_address(struct mip4_ts *ts, u16 *buf_addr)
{
	u8 cmd[] = { MIP4_R0_BOOT, MIP4_R1_BOOT_BUF_ADDR };
	u8 result[sizeof(u16)];
	struct i2c_msg msg[] = {
		{
			.addr = ts->client->addr,
			.flags = 0,
			.buf = cmd,
			.len = sizeof(cmd),
		}, {
			.addr = ts->client->addr,
			.flags = I2C_M_RD,
			.buf = result,
			.len = sizeof(result),
		},
	};
	int ret;
	int error;

	ret = i2c_transfer(ts->client->adapter, msg, ARRAY_SIZE(msg));
	if (ret != ARRAY_SIZE(msg)) {
		error = ret < 0 ? ret : -EIO;
		dev_err(&ts->client->dev,
			"Failed to retrieve bootloader buffer address: %d\n",
			error);
		return error;
	}

	*buf_addr = get_unaligned_le16(result);
	dev_dbg(&ts->client->dev,
		"Bootloader buffer address %#04x\n", *buf_addr);

	return 0;
}