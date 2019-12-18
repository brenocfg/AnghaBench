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
typedef  int u16 ;
struct i2c_msg {int addr; int len; int /*<<< orphan*/ * buf; int /*<<< orphan*/  flags; } ;
struct i2c_client {int addr; int /*<<< orphan*/  dev; int /*<<< orphan*/  adapter; } ;
typedef  int /*<<< orphan*/  bl_data ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  I2C_M_RD ; 
 int IQS5XX_BL_ADDR_MASK ; 
 int IQS5XX_BL_BLK_LEN_MAX ; 
 int /*<<< orphan*/  IQS5XX_BL_CMD_READ ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,...) ; 
 int i2c_transfer (int /*<<< orphan*/ ,struct i2c_msg*,int) ; 
 int iqs5xx_bl_cmd (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int iqs5xx_bl_verify(struct i2c_client *client,
			    u16 bl_addr, u8 *pmap_data, u16 pmap_len)
{
	struct i2c_msg msg;
	int ret, i;
	u8 bl_data[IQS5XX_BL_BLK_LEN_MAX];

	if (pmap_len % IQS5XX_BL_BLK_LEN_MAX)
		return -EINVAL;

	msg.addr = client->addr ^ IQS5XX_BL_ADDR_MASK;
	msg.flags = I2C_M_RD;
	msg.len = sizeof(bl_data);
	msg.buf = bl_data;

	for (i = 0; i < pmap_len; i += IQS5XX_BL_BLK_LEN_MAX) {
		ret = iqs5xx_bl_cmd(client, IQS5XX_BL_CMD_READ, bl_addr + i);
		if (ret)
			return ret;

		ret = i2c_transfer(client->adapter, &msg, 1);
		if (ret != 1)
			goto msg_fail;

		if (memcmp(bl_data, pmap_data + i, sizeof(bl_data))) {
			dev_err(&client->dev,
				"Failed to verify block at address 0x%04X\n",
				bl_addr + i);
			return -EIO;
		}
	}

	return 0;

msg_fail:
	if (ret >= 0)
		ret = -EIO;

	dev_err(&client->dev, "Failed to read block at address 0x%04X: %d\n",
		bl_addr + i, ret);

	return ret;
}