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
struct i2c_msg {int len; int /*<<< orphan*/ * buf; scalar_t__ flags; int /*<<< orphan*/  addr; } ;
struct i2c_client {int /*<<< orphan*/  adapter; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int i2c_transfer (int /*<<< orphan*/ ,struct i2c_msg*,int) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static int da9150_i2c_write_device(struct i2c_client *client, u8 addr,
				   int count, const u8 *buf)
{
	struct i2c_msg xfer;
	u8 *reg_data;
	int ret;

	reg_data = kzalloc(1 + count, GFP_KERNEL);
	if (!reg_data)
		return -ENOMEM;

	reg_data[0] = addr;
	memcpy(&reg_data[1], buf, count);

	/* Write address & data */
	xfer.addr = client->addr;
	xfer.flags = 0;
	xfer.len = 1 + count;
	xfer.buf = reg_data;

	ret = i2c_transfer(client->adapter, &xfer, 1);
	kfree(reg_data);
	if (ret == 1)
		return 0;
	else if (ret < 0)
		return ret;
	else
		return -EIO;
}