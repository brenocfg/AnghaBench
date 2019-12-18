#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int ctrlmode; } ;
struct kvaser_usb_net_priv {size_t channel; TYPE_4__ can; int /*<<< orphan*/  netdev; struct kvaser_usb* dev; } ;
struct TYPE_7__ {int /*<<< orphan*/ * channel_to_he; } ;
struct TYPE_8__ {TYPE_2__ hydra; } ;
struct kvaser_usb {TYPE_3__ card_data; } ;
struct TYPE_10__ {int /*<<< orphan*/  mode; } ;
struct TYPE_6__ {int /*<<< orphan*/  cmd_no; } ;
struct kvaser_cmd {TYPE_5__ set_ctrlmode; TYPE_1__ header; } ;

/* Variables and functions */
 int CAN_CTRLMODE_FD ; 
 int CAN_CTRLMODE_FD_NON_ISO ; 
 int CAN_CTRLMODE_LISTENONLY ; 
 int /*<<< orphan*/  CMD_SET_DRIVERMODE_REQ ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  KVASER_USB_HYDRA_CTRLMODE_LISTEN ; 
 int /*<<< orphan*/  KVASER_USB_HYDRA_CTRLMODE_NORMAL ; 
 struct kvaser_cmd* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct kvaser_cmd*) ; 
 int /*<<< orphan*/  kvaser_usb_hydra_cmd_size (struct kvaser_cmd*) ; 
 int /*<<< orphan*/  kvaser_usb_hydra_get_next_transid (struct kvaser_usb*) ; 
 int /*<<< orphan*/  kvaser_usb_hydra_set_cmd_dest_he (struct kvaser_cmd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvaser_usb_hydra_set_cmd_transid (struct kvaser_cmd*,int /*<<< orphan*/ ) ; 
 int kvaser_usb_send_cmd (struct kvaser_usb*,struct kvaser_cmd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_warn (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int kvaser_usb_hydra_set_opt_mode(const struct kvaser_usb_net_priv *priv)
{
	struct kvaser_usb *dev = priv->dev;
	struct kvaser_cmd *cmd;
	int err;

	if ((priv->can.ctrlmode &
	    (CAN_CTRLMODE_FD | CAN_CTRLMODE_FD_NON_ISO)) ==
	    CAN_CTRLMODE_FD_NON_ISO) {
		netdev_warn(priv->netdev,
			    "CTRLMODE_FD shall be on if CTRLMODE_FD_NON_ISO is on\n");
		return -EINVAL;
	}

	cmd = kcalloc(1, sizeof(struct kvaser_cmd), GFP_KERNEL);
	if (!cmd)
		return -ENOMEM;

	cmd->header.cmd_no = CMD_SET_DRIVERMODE_REQ;
	kvaser_usb_hydra_set_cmd_dest_he
		(cmd, dev->card_data.hydra.channel_to_he[priv->channel]);
	kvaser_usb_hydra_set_cmd_transid
				(cmd, kvaser_usb_hydra_get_next_transid(dev));
	if (priv->can.ctrlmode & CAN_CTRLMODE_LISTENONLY)
		cmd->set_ctrlmode.mode = KVASER_USB_HYDRA_CTRLMODE_LISTEN;
	else
		cmd->set_ctrlmode.mode = KVASER_USB_HYDRA_CTRLMODE_NORMAL;

	err = kvaser_usb_send_cmd(dev, cmd, kvaser_usb_hydra_cmd_size(cmd));
	kfree(cmd);

	return err;
}