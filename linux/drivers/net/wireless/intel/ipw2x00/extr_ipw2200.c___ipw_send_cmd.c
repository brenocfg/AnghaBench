#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct ipw_priv {int status; size_t cmdlog_pos; size_t cmdlog_len; TYPE_2__* cmdlog; int /*<<< orphan*/  lock; int /*<<< orphan*/  wait_command_queue; } ;
struct host_cmd {scalar_t__ cmd; int /*<<< orphan*/  len; scalar_t__ param; } ;
struct TYPE_3__ {scalar_t__ cmd; int /*<<< orphan*/  param; int /*<<< orphan*/  len; } ;
struct TYPE_4__ {int retcode; TYPE_1__ cmd; void* jiffies; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EIO ; 
 unsigned long HOST_COMPLETE_TIMEOUT ; 
 scalar_t__ IPW_CMD_WEP_KEY ; 
 int /*<<< orphan*/  IPW_DEBUG_HC (char*,...) ; 
 int /*<<< orphan*/  IPW_DL_HOST_COMMAND ; 
 int /*<<< orphan*/  IPW_ERROR (char*,int /*<<< orphan*/ ,...) ; 
 int STATUS_HCMD_ACTIVE ; 
 int STATUS_RF_KILL_HW ; 
 int /*<<< orphan*/  get_cmd_string (scalar_t__) ; 
 int ipw_queue_tx_hcmd (struct ipw_priv*,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* jiffies ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk_buf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 
 int wait_event_interruptible_timeout (int /*<<< orphan*/ ,int,unsigned long) ; 

__attribute__((used)) static int __ipw_send_cmd(struct ipw_priv *priv, struct host_cmd *cmd)
{
	int rc = 0;
	unsigned long flags;
	unsigned long now, end;

	spin_lock_irqsave(&priv->lock, flags);
	if (priv->status & STATUS_HCMD_ACTIVE) {
		IPW_ERROR("Failed to send %s: Already sending a command.\n",
			  get_cmd_string(cmd->cmd));
		spin_unlock_irqrestore(&priv->lock, flags);
		return -EAGAIN;
	}

	priv->status |= STATUS_HCMD_ACTIVE;

	if (priv->cmdlog) {
		priv->cmdlog[priv->cmdlog_pos].jiffies = jiffies;
		priv->cmdlog[priv->cmdlog_pos].cmd.cmd = cmd->cmd;
		priv->cmdlog[priv->cmdlog_pos].cmd.len = cmd->len;
		memcpy(priv->cmdlog[priv->cmdlog_pos].cmd.param, cmd->param,
		       cmd->len);
		priv->cmdlog[priv->cmdlog_pos].retcode = -1;
	}

	IPW_DEBUG_HC("%s command (#%d) %d bytes: 0x%08X\n",
		     get_cmd_string(cmd->cmd), cmd->cmd, cmd->len,
		     priv->status);

#ifndef DEBUG_CMD_WEP_KEY
	if (cmd->cmd == IPW_CMD_WEP_KEY)
		IPW_DEBUG_HC("WEP_KEY command masked out for secure.\n");
	else
#endif
		printk_buf(IPW_DL_HOST_COMMAND, (u8 *) cmd->param, cmd->len);

	rc = ipw_queue_tx_hcmd(priv, cmd->cmd, cmd->param, cmd->len, 0);
	if (rc) {
		priv->status &= ~STATUS_HCMD_ACTIVE;
		IPW_ERROR("Failed to send %s: Reason %d\n",
			  get_cmd_string(cmd->cmd), rc);
		spin_unlock_irqrestore(&priv->lock, flags);
		goto exit;
	}
	spin_unlock_irqrestore(&priv->lock, flags);

	now = jiffies;
	end = now + HOST_COMPLETE_TIMEOUT;
again:
	rc = wait_event_interruptible_timeout(priv->wait_command_queue,
					      !(priv->
						status & STATUS_HCMD_ACTIVE),
					      end - now);
	if (rc < 0) {
		now = jiffies;
		if (time_before(now, end))
			goto again;
		rc = 0;
	}

	if (rc == 0) {
		spin_lock_irqsave(&priv->lock, flags);
		if (priv->status & STATUS_HCMD_ACTIVE) {
			IPW_ERROR("Failed to send %s: Command timed out.\n",
				  get_cmd_string(cmd->cmd));
			priv->status &= ~STATUS_HCMD_ACTIVE;
			spin_unlock_irqrestore(&priv->lock, flags);
			rc = -EIO;
			goto exit;
		}
		spin_unlock_irqrestore(&priv->lock, flags);
	} else
		rc = 0;

	if (priv->status & STATUS_RF_KILL_HW) {
		IPW_ERROR("Failed to send %s: Aborted due to RF kill switch.\n",
			  get_cmd_string(cmd->cmd));
		rc = -EIO;
		goto exit;
	}

      exit:
	if (priv->cmdlog) {
		priv->cmdlog[priv->cmdlog_pos++].retcode = rc;
		priv->cmdlog_pos %= priv->cmdlog_len;
	}
	return rc;
}