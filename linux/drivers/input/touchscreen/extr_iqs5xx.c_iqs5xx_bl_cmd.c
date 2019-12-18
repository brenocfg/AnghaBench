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
typedef  int /*<<< orphan*/  u16 ;
struct i2c_msg {int addr; int len; int* buf; scalar_t__ flags; } ;
struct i2c_client {int addr; int /*<<< orphan*/  dev; int /*<<< orphan*/  adapter; } ;
typedef  int /*<<< orphan*/  bl_cmd ;
typedef  int /*<<< orphan*/  bl_addr ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 scalar_t__ I2C_M_RD ; 
 int IQS5XX_BL_ADDR_MASK ; 
#define  IQS5XX_BL_CMD_CRC 131 
#define  IQS5XX_BL_CMD_EXEC 130 
#define  IQS5XX_BL_CMD_READ 129 
#define  IQS5XX_BL_CMD_VER 128 
 int IQS5XX_BL_CRC_PASS ; 
 scalar_t__ IQS5XX_BL_ID ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 scalar_t__ get_unaligned_be16 (int*) ; 
 int i2c_transfer (int /*<<< orphan*/ ,struct i2c_msg*,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  put_unaligned_be16 (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int iqs5xx_bl_cmd(struct i2c_client *client, u8 bl_cmd, u16 bl_addr)
{
	struct i2c_msg msg;
	int ret;
	u8 mbuf[sizeof(bl_cmd) + sizeof(bl_addr)];

	msg.addr = client->addr ^ IQS5XX_BL_ADDR_MASK;
	msg.flags = 0;
	msg.len = sizeof(bl_cmd);
	msg.buf = mbuf;

	*mbuf = bl_cmd;

	switch (bl_cmd) {
	case IQS5XX_BL_CMD_VER:
	case IQS5XX_BL_CMD_CRC:
	case IQS5XX_BL_CMD_EXEC:
		break;
	case IQS5XX_BL_CMD_READ:
		msg.len += sizeof(bl_addr);
		put_unaligned_be16(bl_addr, mbuf + sizeof(bl_cmd));
		break;
	default:
		return -EINVAL;
	}

	ret = i2c_transfer(client->adapter, &msg, 1);
	if (ret != 1)
		goto msg_fail;

	switch (bl_cmd) {
	case IQS5XX_BL_CMD_VER:
		msg.len = sizeof(u16);
		break;
	case IQS5XX_BL_CMD_CRC:
		msg.len = sizeof(u8);
		/*
		 * This delay saves the bus controller the trouble of having to
		 * tolerate a relatively long clock-stretching period while the
		 * CRC is calculated.
		 */
		msleep(50);
		break;
	case IQS5XX_BL_CMD_EXEC:
		usleep_range(10000, 10100);
		/* fall through */
	default:
		return 0;
	}

	msg.flags = I2C_M_RD;

	ret = i2c_transfer(client->adapter, &msg, 1);
	if (ret != 1)
		goto msg_fail;

	if (bl_cmd == IQS5XX_BL_CMD_VER &&
	    get_unaligned_be16(mbuf) != IQS5XX_BL_ID) {
		dev_err(&client->dev, "Unrecognized bootloader ID: 0x%04X\n",
			get_unaligned_be16(mbuf));
		return -EINVAL;
	}

	if (bl_cmd == IQS5XX_BL_CMD_CRC && *mbuf != IQS5XX_BL_CRC_PASS) {
		dev_err(&client->dev, "Bootloader CRC failed\n");
		return -EIO;
	}

	return 0;

msg_fail:
	if (ret >= 0)
		ret = -EIO;

	if (bl_cmd != IQS5XX_BL_CMD_VER)
		dev_err(&client->dev,
			"Unsuccessful bootloader command 0x%02X: %d\n",
			bl_cmd, ret);

	return ret;
}