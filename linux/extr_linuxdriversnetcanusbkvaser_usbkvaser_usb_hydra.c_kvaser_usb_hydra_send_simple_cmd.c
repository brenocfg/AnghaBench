#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_6__ {int /*<<< orphan*/ * channel_to_he; } ;
struct TYPE_7__ {TYPE_2__ hydra; } ;
struct kvaser_usb {TYPE_3__ card_data; TYPE_1__* intf; } ;
struct TYPE_8__ {int /*<<< orphan*/  cmd_no; } ;
struct kvaser_cmd {TYPE_4__ header; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  KVASER_USB_HYDRA_HE_ADDRESS_ILLEGAL ; 
 int KVASER_USB_MAX_NET_DEVICES ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 struct kvaser_cmd* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct kvaser_cmd*) ; 
 int /*<<< orphan*/  kvaser_usb_hydra_cmd_size (struct kvaser_cmd*) ; 
 int /*<<< orphan*/  kvaser_usb_hydra_get_next_transid (struct kvaser_usb*) ; 
 int /*<<< orphan*/  kvaser_usb_hydra_set_cmd_dest_he (struct kvaser_cmd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvaser_usb_hydra_set_cmd_transid (struct kvaser_cmd*,int /*<<< orphan*/ ) ; 
 int kvaser_usb_send_cmd (struct kvaser_usb*,struct kvaser_cmd*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int kvaser_usb_hydra_send_simple_cmd(struct kvaser_usb *dev,
					    u8 cmd_no, int channel)
{
	struct kvaser_cmd *cmd;
	int err;

	cmd = kcalloc(1, sizeof(struct kvaser_cmd), GFP_KERNEL);
	if (!cmd)
		return -ENOMEM;

	cmd->header.cmd_no = cmd_no;
	if (channel < 0) {
		kvaser_usb_hydra_set_cmd_dest_he
				(cmd, KVASER_USB_HYDRA_HE_ADDRESS_ILLEGAL);
	} else {
		if (channel >= KVASER_USB_MAX_NET_DEVICES) {
			dev_err(&dev->intf->dev, "channel (%d) out of range.\n",
				channel);
			err = -EINVAL;
			goto end;
		}
		kvaser_usb_hydra_set_cmd_dest_he
			(cmd, dev->card_data.hydra.channel_to_he[channel]);
	}
	kvaser_usb_hydra_set_cmd_transid
				(cmd, kvaser_usb_hydra_get_next_transid(dev));

	err = kvaser_usb_send_cmd(dev, cmd, kvaser_usb_hydra_cmd_size(cmd));
	if (err)
		goto end;

end:
	kfree(cmd);

	return err;
}