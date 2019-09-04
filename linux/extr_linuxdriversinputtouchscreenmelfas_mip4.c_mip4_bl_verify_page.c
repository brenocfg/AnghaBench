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
struct mip4_ts {TYPE_1__* client; } ;
struct i2c_msg {int len; int /*<<< orphan*/ * buf; int /*<<< orphan*/  flags; int /*<<< orphan*/  addr; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  adapter; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct i2c_msg*) ; 
 int EINVAL ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_M_RD ; 
 int MIP4_BL_PACKET_SIZE ; 
 int /*<<< orphan*/  MIP4_BOOT_CMD_READ ; 
 int /*<<< orphan*/  MIP4_R0_BOOT ; 
 int /*<<< orphan*/  MIP4_R1_BOOT_CMD ; 
 int /*<<< orphan*/  MIP4_R1_BOOT_SIZE ; 
 int /*<<< orphan*/  MIP4_R1_BOOT_TARGET_ADDR ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,...) ; 
 int i2c_master_send (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int i2c_transfer (int /*<<< orphan*/ ,struct i2c_msg*,int) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int) ; 
 int mip4_bl_read_status (struct mip4_ts*) ; 
 int /*<<< orphan*/  put_unaligned_be16 (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_unaligned_le32 (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mip4_bl_verify_page(struct mip4_ts *ts, int offset,
			       const u8 *data, int length, int buf_addr)
{
	u8 cmd[8];
	u8 *read_buf;
	int buf_offset;
	struct i2c_msg msg[] = {
		{
			.addr = ts->client->addr,
			.flags = 0,
			.buf = cmd,
			.len = 2,
		}, {
			.addr = ts->client->addr,
			.flags = I2C_M_RD,
			.len = MIP4_BL_PACKET_SIZE,
		},
	};
	int ret;
	int error;

	dev_dbg(&ts->client->dev, "Validating page @%#06x (%d)\n",
		offset, length);

	/* Addr */
	cmd[0] = MIP4_R0_BOOT;
	cmd[1] = MIP4_R1_BOOT_TARGET_ADDR;
	put_unaligned_le32(offset, &cmd[2]);
	ret = i2c_master_send(ts->client, cmd, 6);
	if (ret != 6) {
		error = ret < 0 ? ret : -EIO;
		dev_err(&ts->client->dev,
			"Failed to send read page address: %d\n", error);
		return error;
	}

	/* Size */
	cmd[0] = MIP4_R0_BOOT;
	cmd[1] = MIP4_R1_BOOT_SIZE;
	put_unaligned_le32(length, &cmd[2]);
	ret = i2c_master_send(ts->client, cmd, 6);
	if (ret != 6) {
		error = ret < 0 ? ret : -EIO;
		dev_err(&ts->client->dev,
			"Failed to send read page size: %d\n", error);
		return error;
	}

	/* Command */
	cmd[0] = MIP4_R0_BOOT;
	cmd[1] = MIP4_R1_BOOT_CMD;
	cmd[2] = MIP4_BOOT_CMD_READ;
	ret = i2c_master_send(ts->client, cmd, 3);
	if (ret != 3) {
		error = ret < 0 ? ret : -EIO;
		dev_err(&ts->client->dev,
			"Failed to send 'read' command: %d\n", error);
		return error;
	}

	/* Status */
	error = mip4_bl_read_status(ts);
	if (error)
		return error;

	/* Read */
	msg[1].buf = read_buf = kmalloc(MIP4_BL_PACKET_SIZE, GFP_KERNEL);
	if (!read_buf)
		return -ENOMEM;

	for (buf_offset = 0;
	     buf_offset < length;
	     buf_offset += MIP4_BL_PACKET_SIZE) {
		dev_dbg(&ts->client->dev,
			"reading chunk at %#04x (size %d)\n",
			buf_offset, MIP4_BL_PACKET_SIZE);
		put_unaligned_be16(buf_addr + buf_offset, cmd);
		ret = i2c_transfer(ts->client->adapter, msg, ARRAY_SIZE(msg));
		if (ret != ARRAY_SIZE(msg)) {
			error = ret < 0 ? ret : -EIO;
			dev_err(&ts->client->dev,
				"Failed to read chunk at %#04x (size %d): %d\n",
				buf_offset, MIP4_BL_PACKET_SIZE, error);
			break;
		}

		if (memcmp(&data[buf_offset], read_buf, MIP4_BL_PACKET_SIZE)) {
			dev_err(&ts->client->dev,
				"Failed to validate chunk at %#04x (size %d)\n",
				buf_offset, MIP4_BL_PACKET_SIZE);
#if MIP4_FW_UPDATE_DEBUG
			print_hex_dump(KERN_DEBUG,
				       MIP4_DEVICE_NAME " F/W File: ",
				       DUMP_PREFIX_OFFSET, 16, 1,
				       data + offset, MIP4_BL_PACKET_SIZE,
				       false);
			print_hex_dump(KERN_DEBUG,
				       MIP4_DEVICE_NAME " F/W Chip: ",
				       DUMP_PREFIX_OFFSET, 16, 1,
				       read_buf, MIP4_BL_PAGE_SIZE, false);
#endif
			error = -EINVAL;
			break;
		}
	}

	kfree(read_buf);
	return error ? error : 0;
}