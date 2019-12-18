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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  u8 ;
struct lbtf_private {int /*<<< orphan*/  command_timer; int /*<<< orphan*/  driver_lock; TYPE_1__* ops; struct cmd_ctrl_node* cur_cmd; } ;
struct cmd_header {int /*<<< orphan*/  seqnum; int /*<<< orphan*/  command; int /*<<< orphan*/  size; } ;
struct cmd_ctrl_node {struct cmd_header* cmdbuf; } ;
struct TYPE_2__ {int (* hw_host_to_card ) (struct lbtf_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  LBTF_DEB_CMD ; 
 int /*<<< orphan*/  LBTF_DEB_HOST ; 
 int /*<<< orphan*/  MVMS_CMD ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  lbtf_deb_cmd (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbtf_deb_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbtf_deb_hex (int /*<<< orphan*/ ,char*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbtf_deb_leave (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  pr_info (char*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int stub1 (struct lbtf_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lbtf_submit_command(struct lbtf_private *priv,
			       struct cmd_ctrl_node *cmdnode)
{
	unsigned long flags;
	struct cmd_header *cmd;
	uint16_t cmdsize;
	uint16_t command;
	int timeo = 5 * HZ;
	int ret;

	lbtf_deb_enter(LBTF_DEB_HOST);

	cmd = cmdnode->cmdbuf;

	spin_lock_irqsave(&priv->driver_lock, flags);
	priv->cur_cmd = cmdnode;
	cmdsize = le16_to_cpu(cmd->size);
	command = le16_to_cpu(cmd->command);

	lbtf_deb_cmd("DNLD_CMD: command 0x%04x, seq %d, size %d\n",
		     command, le16_to_cpu(cmd->seqnum), cmdsize);
	lbtf_deb_hex(LBTF_DEB_CMD, "DNLD_CMD", (void *) cmdnode->cmdbuf, cmdsize);

	ret = priv->ops->hw_host_to_card(priv, MVMS_CMD, (u8 *)cmd, cmdsize);
	spin_unlock_irqrestore(&priv->driver_lock, flags);

	if (ret) {
		pr_info("DNLD_CMD: hw_host_to_card failed: %d\n", ret);
		/* Let the timer kick in and retry, and potentially reset
		   the whole thing if the condition persists */
		timeo = HZ;
	}

	/* Setup the timer after transmit command */
	mod_timer(&priv->command_timer, jiffies + timeo);

	lbtf_deb_leave(LBTF_DEB_HOST);
}