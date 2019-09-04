#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int ctrlmode; } ;
struct kvaser_usb_net_priv {int /*<<< orphan*/  dev; TYPE_1__ can; int /*<<< orphan*/  channel; } ;
struct kvaser_cmd_ctrl_mode {int dummy; } ;
struct TYPE_5__ {int tid; int /*<<< orphan*/  ctrl_mode; int /*<<< orphan*/  channel; } ;
struct TYPE_6__ {TYPE_2__ ctrl_mode; } ;
struct kvaser_cmd {scalar_t__ len; TYPE_3__ u; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int CAN_CTRLMODE_LISTENONLY ; 
 scalar_t__ CMD_HEADER_LEN ; 
 int /*<<< orphan*/  CMD_SET_CTRL_MODE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  KVASER_CTRL_MODE_NORMAL ; 
 int /*<<< orphan*/  KVASER_CTRL_MODE_SILENT ; 
 int /*<<< orphan*/  kfree (struct kvaser_cmd*) ; 
 struct kvaser_cmd* kmalloc (int,int /*<<< orphan*/ ) ; 
 int kvaser_usb_send_cmd (int /*<<< orphan*/ ,struct kvaser_cmd*,scalar_t__) ; 

__attribute__((used)) static int kvaser_usb_leaf_set_opt_mode(const struct kvaser_usb_net_priv *priv)
{
	struct kvaser_cmd *cmd;
	int rc;

	cmd = kmalloc(sizeof(*cmd), GFP_KERNEL);
	if (!cmd)
		return -ENOMEM;

	cmd->id = CMD_SET_CTRL_MODE;
	cmd->len = CMD_HEADER_LEN + sizeof(struct kvaser_cmd_ctrl_mode);
	cmd->u.ctrl_mode.tid = 0xff;
	cmd->u.ctrl_mode.channel = priv->channel;

	if (priv->can.ctrlmode & CAN_CTRLMODE_LISTENONLY)
		cmd->u.ctrl_mode.ctrl_mode = KVASER_CTRL_MODE_SILENT;
	else
		cmd->u.ctrl_mode.ctrl_mode = KVASER_CTRL_MODE_NORMAL;

	rc = kvaser_usb_send_cmd(priv->dev, cmd, cmd->len);

	kfree(cmd);
	return rc;
}