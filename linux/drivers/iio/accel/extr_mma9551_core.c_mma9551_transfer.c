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
typedef  int u16 ;
struct mma9551_mbox_response {int coco_err; int app_id; int nbytes; int req_bytes; int* buf; } ;
struct mma9551_mbox_request {int app_id; int cmd_off; int lower_off; int nbytes; int* buf; scalar_t__ start_mbox; } ;
struct i2c_msg {int len; int* buf; scalar_t__ flags; int /*<<< orphan*/  addr; } ;
struct i2c_client {int /*<<< orphan*/  dev; int /*<<< orphan*/  adapter; int /*<<< orphan*/  addr; } ;
typedef  int /*<<< orphan*/  rsp ;

/* Variables and functions */
 int EINVAL ; 
 int ETIMEDOUT ; 
 scalar_t__ I2C_M_RD ; 
 int MMA9551_CMD_WRITE_CONFIG ; 
 int /*<<< orphan*/  MMA9551_I2C_READ_DELAY ; 
 int MMA9551_I2C_READ_RETRIES ; 
 int MMA9551_MAILBOX_CTRL_REGS ; 
 int MMA9551_MCI_ERROR_NONE ; 
 int MMA9551_RESPONSE_COCO ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int i2c_transfer (int /*<<< orphan*/ ,struct i2c_msg*,int) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mma9551_transfer(struct i2c_client *client,
			    u8 app_id, u8 command, u16 offset,
			    u8 *inbytes, int num_inbytes,
			    u8 *outbytes, int num_outbytes)
{
	struct mma9551_mbox_request req;
	struct mma9551_mbox_response rsp;
	struct i2c_msg in, out;
	u8 req_len, err_code;
	int ret, retries;

	if (offset >= 1 << 12) {
		dev_err(&client->dev, "register offset too large\n");
		return -EINVAL;
	}

	req_len = 1 + MMA9551_MAILBOX_CTRL_REGS + num_inbytes;
	req.start_mbox = 0;
	req.app_id = app_id;
	req.cmd_off = command | (offset >> 8);
	req.lower_off = offset;

	if (command == MMA9551_CMD_WRITE_CONFIG)
		req.nbytes = num_inbytes;
	else
		req.nbytes = num_outbytes;
	if (num_inbytes)
		memcpy(req.buf, inbytes, num_inbytes);

	out.addr = client->addr;
	out.flags = 0;
	out.len = req_len;
	out.buf = (u8 *)&req;

	ret = i2c_transfer(client->adapter, &out, 1);
	if (ret < 0) {
		dev_err(&client->dev, "i2c write failed\n");
		return ret;
	}

	retries = MMA9551_I2C_READ_RETRIES;
	do {
		udelay(MMA9551_I2C_READ_DELAY);

		in.addr = client->addr;
		in.flags = I2C_M_RD;
		in.len = sizeof(rsp);
		in.buf = (u8 *)&rsp;

		ret = i2c_transfer(client->adapter, &in, 1);
		if (ret < 0) {
			dev_err(&client->dev, "i2c read failed\n");
			return ret;
		}

		if (rsp.coco_err & MMA9551_RESPONSE_COCO)
			break;
	} while (--retries > 0);

	if (retries == 0) {
		dev_err(&client->dev,
			"timed out while waiting for command response\n");
		return -ETIMEDOUT;
	}

	if (rsp.app_id != app_id) {
		dev_err(&client->dev,
			"app_id mismatch in response got %02x expected %02x\n",
			rsp.app_id, app_id);
		return -EINVAL;
	}

	err_code = rsp.coco_err & ~MMA9551_RESPONSE_COCO;
	if (err_code != MMA9551_MCI_ERROR_NONE) {
		dev_err(&client->dev, "read returned error %x\n", err_code);
		return -EINVAL;
	}

	if (rsp.nbytes != rsp.req_bytes) {
		dev_err(&client->dev,
			"output length mismatch got %d expected %d\n",
			rsp.nbytes, rsp.req_bytes);
		return -EINVAL;
	}

	if (num_outbytes)
		memcpy(outbytes, rsp.buf, num_outbytes);

	return 0;
}