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
struct kvaser_usb_net_priv {int /*<<< orphan*/  dev; int /*<<< orphan*/  channel; } ;
struct kvaser_cmd_flush_queue {int dummy; } ;
struct TYPE_3__ {int flags; int /*<<< orphan*/  channel; } ;
struct TYPE_4__ {TYPE_1__ flush_queue; } ;
struct kvaser_cmd {scalar_t__ len; TYPE_2__ u; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_FLUSH_QUEUE ; 
 scalar_t__ CMD_HEADER_LEN ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct kvaser_cmd*) ; 
 struct kvaser_cmd* kmalloc (int,int /*<<< orphan*/ ) ; 
 int kvaser_usb_send_cmd (int /*<<< orphan*/ ,struct kvaser_cmd*,scalar_t__) ; 

__attribute__((used)) static int kvaser_usb_leaf_flush_queue(struct kvaser_usb_net_priv *priv)
{
	struct kvaser_cmd *cmd;
	int rc;

	cmd = kmalloc(sizeof(*cmd), GFP_KERNEL);
	if (!cmd)
		return -ENOMEM;

	cmd->id = CMD_FLUSH_QUEUE;
	cmd->len = CMD_HEADER_LEN + sizeof(struct kvaser_cmd_flush_queue);
	cmd->u.flush_queue.channel = priv->channel;
	cmd->u.flush_queue.flags = 0x00;

	rc = kvaser_usb_send_cmd(priv->dev, cmd, cmd->len);

	kfree(cmd);
	return rc;
}