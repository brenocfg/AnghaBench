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
struct i2c_client {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  reg ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int IQS5XX_NUM_RETRIES ; 
 int IQS5XX_WR_BYTES_MAX ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,int) ; 
 int i2c_master_send (struct i2c_client*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,void const*,int) ; 
 int /*<<< orphan*/  put_unaligned_be16 (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int iqs5xx_write_burst(struct i2c_client *client,
			      u16 reg, const void *val, u16 len)
{
	int ret, i;
	u16 mlen = sizeof(reg) + len;
	u8 mbuf[sizeof(reg) + IQS5XX_WR_BYTES_MAX];

	if (len > IQS5XX_WR_BYTES_MAX)
		return -EINVAL;

	put_unaligned_be16(reg, mbuf);
	memcpy(mbuf + sizeof(reg), val, len);

	/*
	 * The first addressing attempt outside of a communication window fails
	 * and must be retried, after which the device clock stretches until it
	 * is available.
	 */
	for (i = 0; i < IQS5XX_NUM_RETRIES; i++) {
		ret = i2c_master_send(client, mbuf, mlen);
		if (ret == mlen)
			return 0;

		usleep_range(200, 300);
	}

	if (ret >= 0)
		ret = -EIO;

	dev_err(&client->dev, "Failed to write to address 0x%04X: %d\n",
		reg, ret);

	return ret;
}