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
struct i2c_client {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int EINVAL ; 
 int /*<<< orphan*/  MMA9551_CMD_READ_STATUS ; 
 int MMA9551_MAX_MAILBOX_DATA_REGS ; 
 int /*<<< orphan*/  be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int mma9551_transfer (struct i2c_client*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int) ; 

int mma9551_read_status_words(struct i2c_client *client, u8 app_id,
			      u16 reg, u8 len, u16 *buf)
{
	int ret, i;
	__be16 be_buf[MMA9551_MAX_MAILBOX_DATA_REGS / 2];

	if (len > ARRAY_SIZE(be_buf)) {
		dev_err(&client->dev, "Invalid buffer size %d\n", len);
		return -EINVAL;
	}

	ret = mma9551_transfer(client, app_id, MMA9551_CMD_READ_STATUS,
			       reg, NULL, 0, (u8 *)be_buf, len * sizeof(u16));
	if (ret < 0)
		return ret;

	for (i = 0; i < len; i++)
		buf[i] = be16_to_cpu(be_buf[i]);

	return 0;
}