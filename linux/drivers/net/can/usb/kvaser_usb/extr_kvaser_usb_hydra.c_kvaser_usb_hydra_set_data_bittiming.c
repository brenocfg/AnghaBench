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
typedef  void* u8 ;
struct net_device {int dummy; } ;
struct can_bittiming {int prop_seg; int phase_seg1; int phase_seg2; int sjw; int /*<<< orphan*/  bitrate; } ;
struct TYPE_7__ {int ctrlmode; struct can_bittiming data_bittiming; } ;
struct kvaser_usb_net_priv {size_t channel; TYPE_2__ can; struct kvaser_usb* dev; } ;
struct TYPE_9__ {int /*<<< orphan*/ * channel_to_he; } ;
struct TYPE_10__ {TYPE_4__ hydra; } ;
struct kvaser_usb {TYPE_5__ card_data; } ;
struct TYPE_8__ {int nsamples_d; int /*<<< orphan*/  canfd_mode; void* tseg2_d; void* tseg1_d; void* sjw_d; int /*<<< orphan*/  bitrate_d; } ;
struct TYPE_6__ {int /*<<< orphan*/  cmd_no; } ;
struct kvaser_cmd {TYPE_3__ set_busparams_req; TYPE_1__ header; } ;

/* Variables and functions */
 int CAN_CTRLMODE_FD ; 
 int CAN_CTRLMODE_FD_NON_ISO ; 
 int /*<<< orphan*/  CMD_SET_BUSPARAMS_FD_REQ ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  KVASER_USB_HYDRA_BUS_MODE_CANFD_ISO ; 
 int /*<<< orphan*/  KVASER_USB_HYDRA_BUS_MODE_NONISO ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 struct kvaser_cmd* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct kvaser_cmd*) ; 
 int /*<<< orphan*/  kvaser_usb_hydra_cmd_size (struct kvaser_cmd*) ; 
 int /*<<< orphan*/  kvaser_usb_hydra_get_next_transid (struct kvaser_usb*) ; 
 int /*<<< orphan*/  kvaser_usb_hydra_set_cmd_dest_he (struct kvaser_cmd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvaser_usb_hydra_set_cmd_transid (struct kvaser_cmd*,int /*<<< orphan*/ ) ; 
 int kvaser_usb_send_cmd (struct kvaser_usb*,struct kvaser_cmd*,int /*<<< orphan*/ ) ; 
 struct kvaser_usb_net_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int kvaser_usb_hydra_set_data_bittiming(struct net_device *netdev)
{
	struct kvaser_cmd *cmd;
	struct kvaser_usb_net_priv *priv = netdev_priv(netdev);
	struct can_bittiming *dbt = &priv->can.data_bittiming;
	struct kvaser_usb *dev = priv->dev;
	int tseg1 = dbt->prop_seg + dbt->phase_seg1;
	int tseg2 = dbt->phase_seg2;
	int sjw = dbt->sjw;
	int err;

	cmd = kcalloc(1, sizeof(struct kvaser_cmd), GFP_KERNEL);
	if (!cmd)
		return -ENOMEM;

	cmd->header.cmd_no = CMD_SET_BUSPARAMS_FD_REQ;
	cmd->set_busparams_req.bitrate_d = cpu_to_le32(dbt->bitrate);
	cmd->set_busparams_req.sjw_d = (u8)sjw;
	cmd->set_busparams_req.tseg1_d = (u8)tseg1;
	cmd->set_busparams_req.tseg2_d = (u8)tseg2;
	cmd->set_busparams_req.nsamples_d = 1;

	if (priv->can.ctrlmode & CAN_CTRLMODE_FD) {
		if (priv->can.ctrlmode & CAN_CTRLMODE_FD_NON_ISO)
			cmd->set_busparams_req.canfd_mode =
					KVASER_USB_HYDRA_BUS_MODE_NONISO;
		else
			cmd->set_busparams_req.canfd_mode =
					KVASER_USB_HYDRA_BUS_MODE_CANFD_ISO;
	}

	kvaser_usb_hydra_set_cmd_dest_he
		(cmd, dev->card_data.hydra.channel_to_he[priv->channel]);
	kvaser_usb_hydra_set_cmd_transid
				(cmd, kvaser_usb_hydra_get_next_transid(dev));

	err = kvaser_usb_send_cmd(dev, cmd, kvaser_usb_hydra_cmd_size(cmd));

	kfree(cmd);

	return err;
}