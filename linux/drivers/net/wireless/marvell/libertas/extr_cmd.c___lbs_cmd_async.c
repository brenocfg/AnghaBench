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
typedef  int uint16_t ;
struct lbs_private {int /*<<< orphan*/  waitq; scalar_t__ is_deep_sleep; int /*<<< orphan*/  is_auto_deep_sleep_enabled; scalar_t__ surpriseremoved; } ;
struct cmd_header {int dummy; } ;
struct cmd_ctrl_node {int (* callback ) (struct lbs_private*,unsigned long,struct cmd_header*) ;unsigned long callback_arg; scalar_t__ cmdwaitqwoken; TYPE_1__* cmdbuf; } ;
struct TYPE_2__ {scalar_t__ result; void* size; void* command; } ;

/* Variables and functions */
 int /*<<< orphan*/  EBUSY ; 
 int /*<<< orphan*/  ENOBUFS ; 
 int /*<<< orphan*/  ENOENT ; 
 struct cmd_ctrl_node* ERR_PTR (int /*<<< orphan*/ ) ; 
 void* cpu_to_le16 (int) ; 
 int /*<<< orphan*/  lbs_deb_cmd (char*) ; 
 int /*<<< orphan*/  lbs_deb_host (char*,...) ; 
 struct cmd_ctrl_node* lbs_get_free_cmd_node (struct lbs_private*) ; 
 int /*<<< orphan*/  lbs_queue_cmd (struct lbs_private*,struct cmd_ctrl_node*) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,struct cmd_header*,int) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

struct cmd_ctrl_node *__lbs_cmd_async(struct lbs_private *priv,
	uint16_t command, struct cmd_header *in_cmd, int in_cmd_size,
	int (*callback)(struct lbs_private *, unsigned long, struct cmd_header *),
	unsigned long callback_arg)
{
	struct cmd_ctrl_node *cmdnode;

	if (priv->surpriseremoved) {
		lbs_deb_host("PREP_CMD: card removed\n");
		cmdnode = ERR_PTR(-ENOENT);
		goto done;
	}

	/* No commands are allowed in Deep Sleep until we toggle the GPIO
	 * to wake up the card and it has signaled that it's ready.
	 */
	if (!priv->is_auto_deep_sleep_enabled) {
		if (priv->is_deep_sleep) {
			lbs_deb_cmd("command not allowed in deep sleep\n");
			cmdnode = ERR_PTR(-EBUSY);
			goto done;
		}
	}

	cmdnode = lbs_get_free_cmd_node(priv);
	if (cmdnode == NULL) {
		lbs_deb_host("PREP_CMD: cmdnode is NULL\n");

		/* Wake up main thread to execute next command */
		wake_up(&priv->waitq);
		cmdnode = ERR_PTR(-ENOBUFS);
		goto done;
	}

	cmdnode->callback = callback;
	cmdnode->callback_arg = callback_arg;

	/* Copy the incoming command to the buffer */
	memcpy(cmdnode->cmdbuf, in_cmd, in_cmd_size);

	/* Set command, clean result, move to buffer */
	cmdnode->cmdbuf->command = cpu_to_le16(command);
	cmdnode->cmdbuf->size    = cpu_to_le16(in_cmd_size);
	cmdnode->cmdbuf->result  = 0;

	lbs_deb_host("PREP_CMD: command 0x%04x\n", command);

	cmdnode->cmdwaitqwoken = 0;
	lbs_queue_cmd(priv, cmdnode);
	wake_up(&priv->waitq);

 done:
	return cmdnode;
}