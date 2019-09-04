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
typedef  int /*<<< orphan*/  u16 ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  cmd_buf ;

/* Variables and functions */
 int CMD_BUF_SIZE ; 
 size_t CMD_INDEX_OFFSET ; 
 size_t CMD_KEY_OFFSET ; 
 size_t CMD_LENGTH_OFFSET ; 
 size_t CMD_REPORT_ID_OFFSET ; 
 int /*<<< orphan*/  CMD_SFLCK_KEY ; 
 int /*<<< orphan*/  CMD_SFUNL_KEY ; 
 size_t CMD_TYPE_OFFSET ; 
 int EINVAL ; 
#define  VND_CMD_ERASE 135 
#define  VND_CMD_RESET 134 
#define  VND_CMD_SFLCK 133 
#define  VND_CMD_SFUNL 132 
#define  VND_CMD_START 131 
#define  VND_CMD_STOP 130 
 int /*<<< orphan*/  VND_REQ_WRITE ; 
#define  VND_SET_CHECKSUM_CALC 129 
#define  VND_SET_CHECKSUM_LENGTH 128 
 int /*<<< orphan*/  VND_SET_COMMAND_DATA ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  put_unaligned_le16 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_unaligned_le32 (int,int /*<<< orphan*/ *) ; 
 int wdt87xx_set_feature (struct i2c_client*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int wdt87xx_send_command(struct i2c_client *client, int cmd, int value)
{
	u8 cmd_buf[CMD_BUF_SIZE];

	/* Set the command packet */
	cmd_buf[CMD_REPORT_ID_OFFSET] = VND_REQ_WRITE;
	cmd_buf[CMD_TYPE_OFFSET] = VND_SET_COMMAND_DATA;
	put_unaligned_le16((u16)cmd, &cmd_buf[CMD_INDEX_OFFSET]);

	switch (cmd) {
	case VND_CMD_START:
	case VND_CMD_STOP:
	case VND_CMD_RESET:
		/* Mode selector */
		put_unaligned_le32((value & 0xFF), &cmd_buf[CMD_LENGTH_OFFSET]);
		break;

	case VND_CMD_SFLCK:
		put_unaligned_le16(CMD_SFLCK_KEY, &cmd_buf[CMD_KEY_OFFSET]);
		break;

	case VND_CMD_SFUNL:
		put_unaligned_le16(CMD_SFUNL_KEY, &cmd_buf[CMD_KEY_OFFSET]);
		break;

	case VND_CMD_ERASE:
	case VND_SET_CHECKSUM_CALC:
	case VND_SET_CHECKSUM_LENGTH:
		put_unaligned_le32(value, &cmd_buf[CMD_KEY_OFFSET]);
		break;

	default:
		cmd_buf[CMD_REPORT_ID_OFFSET] = 0;
		dev_err(&client->dev, "Invalid command: %d\n", cmd);
		return -EINVAL;
	}

	return wdt87xx_set_feature(client, cmd_buf, sizeof(cmd_buf));
}