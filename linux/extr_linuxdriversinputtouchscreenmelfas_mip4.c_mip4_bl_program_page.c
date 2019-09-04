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
typedef  int u16 ;
struct mip4_ts {TYPE_1__* client; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MIP4_BL_PACKET_SIZE ; 
 int MIP4_BL_PAGE_SIZE ; 
 int /*<<< orphan*/  MIP4_BOOT_CMD_PROGRAM ; 
 int /*<<< orphan*/  MIP4_R0_BOOT ; 
 int /*<<< orphan*/  MIP4_R1_BOOT_CMD ; 
 int /*<<< orphan*/  MIP4_R1_BOOT_SIZE ; 
 int /*<<< orphan*/  MIP4_R1_BOOT_TARGET_ADDR ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,...) ; 
 int i2c_master_send (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int mip4_bl_read_status (struct mip4_ts*) ; 
 int /*<<< orphan*/  put_unaligned_be16 (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_unaligned_le32 (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mip4_bl_program_page(struct mip4_ts *ts, int offset,
				const u8 *data, int length, u16 buf_addr)
{
	u8 cmd[6];
	u8 *data_buf;
	u16 buf_offset;
	int ret;
	int error;

	dev_dbg(&ts->client->dev, "Writing page @%#06x (%d)\n",
		offset, length);

	if (length > MIP4_BL_PAGE_SIZE || length % MIP4_BL_PACKET_SIZE) {
		dev_err(&ts->client->dev,
			"Invalid page length: %d\n", length);
		return -EINVAL;
	}

	data_buf = kmalloc(2 + MIP4_BL_PACKET_SIZE, GFP_KERNEL);
	if (!data_buf)
		return -ENOMEM;

	/* Addr */
	cmd[0] = MIP4_R0_BOOT;
	cmd[1] = MIP4_R1_BOOT_TARGET_ADDR;
	put_unaligned_le32(offset, &cmd[2]);
	ret = i2c_master_send(ts->client, cmd, 6);
	if (ret != 6) {
		error = ret < 0 ? ret : -EIO;
		dev_err(&ts->client->dev,
			"Failed to send write page address: %d\n", error);
		goto out;
	}

	/* Size */
	cmd[0] = MIP4_R0_BOOT;
	cmd[1] = MIP4_R1_BOOT_SIZE;
	put_unaligned_le32(length, &cmd[2]);
	ret = i2c_master_send(ts->client, cmd, 6);
	if (ret != 6) {
		error = ret < 0 ? ret : -EIO;
		dev_err(&ts->client->dev,
			"Failed to send write page size: %d\n", error);
		goto out;
	}

	/* Data */
	for (buf_offset = 0;
	     buf_offset < length;
	     buf_offset += MIP4_BL_PACKET_SIZE) {
		dev_dbg(&ts->client->dev,
			"writing chunk at %#04x (size %d)\n",
			buf_offset, MIP4_BL_PACKET_SIZE);
		put_unaligned_be16(buf_addr + buf_offset, data_buf);
		memcpy(&data_buf[2], &data[buf_offset], MIP4_BL_PACKET_SIZE);
		ret = i2c_master_send(ts->client,
				      data_buf, 2 + MIP4_BL_PACKET_SIZE);
		if (ret != 2 + MIP4_BL_PACKET_SIZE) {
			error = ret < 0 ? ret : -EIO;
			dev_err(&ts->client->dev,
				"Failed to read chunk at %#04x (size %d): %d\n",
				buf_offset, MIP4_BL_PACKET_SIZE, error);
			goto out;
		}
	}

	/* Command */
	cmd[0] = MIP4_R0_BOOT;
	cmd[1] = MIP4_R1_BOOT_CMD;
	cmd[2] = MIP4_BOOT_CMD_PROGRAM;
	ret = i2c_master_send(ts->client, cmd, 3);
	if (ret != 3) {
		error = ret < 0 ? ret : -EIO;
		dev_err(&ts->client->dev,
			"Failed to send 'write' command: %d\n", error);
		goto out;
	}

	/* Status */
	error = mip4_bl_read_status(ts);

out:
	kfree(data_buf);
	return error ? error : 0;
}