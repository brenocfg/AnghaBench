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
struct ucsi_ccg {int cmd_resp; int /*<<< orphan*/  flags; struct device* dev; } ;
struct device {int dummy; } ;
struct ccg_cmd {int reg; int /*<<< orphan*/  delay; int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEV_CMD_PENDING ; 
#define  DEV_REG_IDX 128 
 int EIO ; 
 int /*<<< orphan*/  ccg_process_response (struct ucsi_ccg*) ; 
 int ccg_read_response (struct ucsi_ccg*) ; 
 int ccg_write (struct ucsi_ccg*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ccg_send_command(struct ucsi_ccg *uc, struct ccg_cmd *cmd)
{
	struct device *dev = uc->dev;
	int ret;

	switch (cmd->reg & 0xF000) {
	case DEV_REG_IDX:
		set_bit(DEV_CMD_PENDING, &uc->flags);
		break;
	default:
		dev_err(dev, "invalid cmd register\n");
		break;
	}

	ret = ccg_write(uc, cmd->reg, (u8 *)&cmd->data, cmd->len);
	if (ret < 0)
		return ret;

	msleep(cmd->delay);

	ret = ccg_read_response(uc);
	if (ret < 0) {
		dev_err(dev, "response read error\n");
		switch (cmd->reg & 0xF000) {
		case DEV_REG_IDX:
			clear_bit(DEV_CMD_PENDING, &uc->flags);
			break;
		default:
			dev_err(dev, "invalid cmd register\n");
			break;
		}
		return -EIO;
	}
	ccg_process_response(uc);

	return uc->cmd_resp;
}