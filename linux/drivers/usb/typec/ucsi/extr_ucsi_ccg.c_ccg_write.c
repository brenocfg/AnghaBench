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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct ucsi_ccg {int /*<<< orphan*/  dev; struct i2c_client* client; } ;
struct i2c_msg {int flags; unsigned char* buf; scalar_t__ len; int /*<<< orphan*/  addr; } ;
struct i2c_client {int /*<<< orphan*/  adapter; int /*<<< orphan*/  addr; } ;
typedef  int /*<<< orphan*/  rab ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (struct i2c_msg*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int i2c_transfer (int /*<<< orphan*/ ,struct i2c_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (unsigned char*) ; 
 unsigned char* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_unaligned_le16 (int /*<<< orphan*/ ,unsigned char*) ; 

__attribute__((used)) static int ccg_write(struct ucsi_ccg *uc, u16 rab, u8 *data, u32 len)
{
	struct i2c_client *client = uc->client;
	unsigned char *buf;
	struct i2c_msg msgs[] = {
		{
			.addr	= client->addr,
			.flags  = 0x0,
		}
	};
	int status;

	buf = kzalloc(len + sizeof(rab), GFP_KERNEL);
	if (!buf)
		return -ENOMEM;

	put_unaligned_le16(rab, buf);
	memcpy(buf + sizeof(rab), data, len);

	msgs[0].len = len + sizeof(rab);
	msgs[0].buf = buf;

	pm_runtime_get_sync(uc->dev);
	status = i2c_transfer(client->adapter, msgs, ARRAY_SIZE(msgs));
	if (status < 0) {
		dev_err(uc->dev, "i2c_transfer failed %d\n", status);
		pm_runtime_put_sync(uc->dev);
		kfree(buf);
		return status;
	}

	pm_runtime_put_sync(uc->dev);
	kfree(buf);
	return 0;
}