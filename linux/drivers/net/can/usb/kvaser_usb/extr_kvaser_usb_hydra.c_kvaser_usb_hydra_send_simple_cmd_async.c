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
typedef  int /*<<< orphan*/  u8 ;
struct kvaser_usb_net_priv {size_t channel; struct kvaser_usb* dev; } ;
struct TYPE_5__ {int /*<<< orphan*/ * channel_to_he; } ;
struct TYPE_6__ {TYPE_2__ hydra; } ;
struct kvaser_usb {TYPE_3__ card_data; } ;
struct TYPE_4__ {int /*<<< orphan*/  cmd_no; } ;
struct kvaser_cmd {TYPE_1__ header; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 struct kvaser_cmd* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct kvaser_cmd*) ; 
 int /*<<< orphan*/  kvaser_usb_hydra_cmd_size (struct kvaser_cmd*) ; 
 int /*<<< orphan*/  kvaser_usb_hydra_get_next_transid (struct kvaser_usb*) ; 
 int /*<<< orphan*/  kvaser_usb_hydra_set_cmd_dest_he (struct kvaser_cmd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvaser_usb_hydra_set_cmd_transid (struct kvaser_cmd*,int /*<<< orphan*/ ) ; 
 int kvaser_usb_send_cmd_async (struct kvaser_usb_net_priv*,struct kvaser_cmd*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
kvaser_usb_hydra_send_simple_cmd_async(struct kvaser_usb_net_priv *priv,
				       u8 cmd_no)
{
	struct kvaser_cmd *cmd;
	struct kvaser_usb *dev = priv->dev;
	int err;

	cmd = kcalloc(1, sizeof(struct kvaser_cmd), GFP_ATOMIC);
	if (!cmd)
		return -ENOMEM;

	cmd->header.cmd_no = cmd_no;

	kvaser_usb_hydra_set_cmd_dest_he
		(cmd, dev->card_data.hydra.channel_to_he[priv->channel]);
	kvaser_usb_hydra_set_cmd_transid
				(cmd, kvaser_usb_hydra_get_next_transid(dev));

	err = kvaser_usb_send_cmd_async(priv, cmd,
					kvaser_usb_hydra_cmd_size(cmd));
	if (err)
		kfree(cmd);

	return err;
}