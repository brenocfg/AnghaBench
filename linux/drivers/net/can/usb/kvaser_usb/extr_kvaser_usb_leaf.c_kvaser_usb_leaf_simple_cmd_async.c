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
struct kvaser_usb_net_priv {int /*<<< orphan*/  channel; } ;
struct kvaser_cmd_simple {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  channel; } ;
struct TYPE_4__ {TYPE_1__ simple; } ;
struct kvaser_cmd {scalar_t__ len; TYPE_2__ u; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 scalar_t__ CMD_HEADER_LEN ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  kfree (struct kvaser_cmd*) ; 
 struct kvaser_cmd* kmalloc (int,int /*<<< orphan*/ ) ; 
 int kvaser_usb_send_cmd_async (struct kvaser_usb_net_priv*,struct kvaser_cmd*,scalar_t__) ; 

__attribute__((used)) static int kvaser_usb_leaf_simple_cmd_async(struct kvaser_usb_net_priv *priv,
					    u8 cmd_id)
{
	struct kvaser_cmd *cmd;
	int err;

	cmd = kmalloc(sizeof(*cmd), GFP_ATOMIC);
	if (!cmd)
		return -ENOMEM;

	cmd->len = CMD_HEADER_LEN + sizeof(struct kvaser_cmd_simple);
	cmd->id = cmd_id;
	cmd->u.simple.channel = priv->channel;

	err = kvaser_usb_send_cmd_async(priv, cmd, cmd->len);
	if (err)
		kfree(cmd);

	return err;
}