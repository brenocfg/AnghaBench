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
struct i2c_msg {int addr; int len; int /*<<< orphan*/ * buf; scalar_t__ flags; } ;
struct i2c_client {int addr; int /*<<< orphan*/  dev; int /*<<< orphan*/  adapter; } ;
typedef  int /*<<< orphan*/  mbuf ;
typedef  int /*<<< orphan*/  bl_addr ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int IQS5XX_BL_ADDR_MASK ; 
 int IQS5XX_BL_BLK_LEN_MAX ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,int) ; 
 int i2c_transfer (int /*<<< orphan*/ ,struct i2c_msg*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  put_unaligned_be16 (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int iqs5xx_bl_write(struct i2c_client *client,
			   u16 bl_addr, u8 *pmap_data, u16 pmap_len)
{
	struct i2c_msg msg;
	int ret, i;
	u8 mbuf[sizeof(bl_addr) + IQS5XX_BL_BLK_LEN_MAX];

	if (pmap_len % IQS5XX_BL_BLK_LEN_MAX)
		return -EINVAL;

	msg.addr = client->addr ^ IQS5XX_BL_ADDR_MASK;
	msg.flags = 0;
	msg.len = sizeof(mbuf);
	msg.buf = mbuf;

	for (i = 0; i < pmap_len; i += IQS5XX_BL_BLK_LEN_MAX) {
		put_unaligned_be16(bl_addr + i, mbuf);
		memcpy(mbuf + sizeof(bl_addr), pmap_data + i,
		       sizeof(mbuf) - sizeof(bl_addr));

		ret = i2c_transfer(client->adapter, &msg, 1);
		if (ret != 1)
			goto msg_fail;

		usleep_range(10000, 10100);
	}

	return 0;

msg_fail:
	if (ret >= 0)
		ret = -EIO;

	dev_err(&client->dev, "Failed to write block at address 0x%04X: %d\n",
		bl_addr + i, ret);

	return ret;
}