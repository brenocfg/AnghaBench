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
typedef  int /*<<< orphan*/  u16 ;
struct kvaser_usb {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  channel; int /*<<< orphan*/  name; } ;
struct TYPE_4__ {int /*<<< orphan*/  cmd_no; } ;
struct kvaser_cmd {TYPE_1__ map_ch_req; TYPE_2__ header; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_MAP_CHANNEL_REQ ; 
 int /*<<< orphan*/  CMD_MAP_CHANNEL_RESP ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  KVASER_USB_HYDRA_HE_ADDRESS_ROUTER ; 
 struct kvaser_cmd* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct kvaser_cmd*) ; 
 int /*<<< orphan*/  kvaser_usb_hydra_cmd_size (struct kvaser_cmd*) ; 
 int kvaser_usb_hydra_map_channel_resp (struct kvaser_usb*,struct kvaser_cmd*) ; 
 int /*<<< orphan*/  kvaser_usb_hydra_set_cmd_dest_he (struct kvaser_cmd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvaser_usb_hydra_set_cmd_transid (struct kvaser_cmd*,int /*<<< orphan*/ ) ; 
 int kvaser_usb_hydra_wait_cmd (struct kvaser_usb*,int /*<<< orphan*/ ,struct kvaser_cmd*) ; 
 int kvaser_usb_send_cmd (struct kvaser_usb*,struct kvaser_cmd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int kvaser_usb_hydra_map_channel(struct kvaser_usb *dev, u16 transid,
					u8 channel, const char *name)
{
	struct kvaser_cmd *cmd;
	int err;

	cmd = kcalloc(1, sizeof(struct kvaser_cmd), GFP_KERNEL);
	if (!cmd)
		return -ENOMEM;

	strcpy(cmd->map_ch_req.name, name);
	cmd->header.cmd_no = CMD_MAP_CHANNEL_REQ;
	kvaser_usb_hydra_set_cmd_dest_he
				(cmd, KVASER_USB_HYDRA_HE_ADDRESS_ROUTER);
	cmd->map_ch_req.channel = channel;

	kvaser_usb_hydra_set_cmd_transid(cmd, transid);

	err = kvaser_usb_send_cmd(dev, cmd, kvaser_usb_hydra_cmd_size(cmd));
	if (err)
		goto end;

	err = kvaser_usb_hydra_wait_cmd(dev, CMD_MAP_CHANNEL_RESP, cmd);
	if (err)
		goto end;

	err = kvaser_usb_hydra_map_channel_resp(dev, cmd);
	if (err)
		goto end;

end:
	kfree(cmd);

	return err;
}