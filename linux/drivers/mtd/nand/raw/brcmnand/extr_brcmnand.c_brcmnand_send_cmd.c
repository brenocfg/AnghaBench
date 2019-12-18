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
typedef  int /*<<< orphan*/  u64 ;
struct brcmnand_host {struct brcmnand_controller* ctrl; } ;
struct brcmnand_controller {int cmd_pending; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRCMNAND_CMD_ADDRESS ; 
 int /*<<< orphan*/  BRCMNAND_CMD_START ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  NAND_CTRL_RDY ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int bcmnand_ctrl_poll_status (struct brcmnand_controller*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int brcmnand_cmd_shift (struct brcmnand_controller*) ; 
 int /*<<< orphan*/  brcmnand_read_reg (struct brcmnand_controller*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcmnand_write_reg (struct brcmnand_controller*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mb () ; 

__attribute__((used)) static void brcmnand_send_cmd(struct brcmnand_host *host, int cmd)
{
	struct brcmnand_controller *ctrl = host->ctrl;
	int ret;
	u64 cmd_addr;

	cmd_addr = brcmnand_read_reg(ctrl, BRCMNAND_CMD_ADDRESS);

	dev_dbg(ctrl->dev, "send native cmd %d addr 0x%llx\n", cmd, cmd_addr);

	BUG_ON(ctrl->cmd_pending != 0);
	ctrl->cmd_pending = cmd;

	ret = bcmnand_ctrl_poll_status(ctrl, NAND_CTRL_RDY, NAND_CTRL_RDY, 0);
	WARN_ON(ret);

	mb(); /* flush previous writes */
	brcmnand_write_reg(ctrl, BRCMNAND_CMD_START,
			   cmd << brcmnand_cmd_shift(ctrl));
}