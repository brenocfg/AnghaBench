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
typedef  size_t u8 ;
typedef  int u16 ;
struct kvaser_usb_dev_card_data_hydra {size_t* channel_to_he; size_t sysdbg_he; } ;
struct TYPE_4__ {struct kvaser_usb_dev_card_data_hydra hydra; } ;
struct kvaser_usb {TYPE_3__* intf; TYPE_1__ card_data; } ;
struct TYPE_5__ {size_t he_addr; } ;
struct kvaser_cmd {TYPE_2__ map_ch_res; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
#define  KVASER_USB_HYDRA_TRANSID_CANHE 129 
#define  KVASER_USB_HYDRA_TRANSID_SYSDBG 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 int kvaser_usb_hydra_get_cmd_transid (struct kvaser_cmd const*) ; 

__attribute__((used)) static int kvaser_usb_hydra_map_channel_resp(struct kvaser_usb *dev,
					     const struct kvaser_cmd *cmd)
{
	u8 he, channel;
	u16 transid = kvaser_usb_hydra_get_cmd_transid(cmd);
	struct kvaser_usb_dev_card_data_hydra *card_data =
							&dev->card_data.hydra;

	if (transid > 0x007f || transid < 0x0040) {
		dev_err(&dev->intf->dev,
			"CMD_MAP_CHANNEL_RESP, invalid transid: 0x%x\n",
			transid);
		return -EINVAL;
	}

	switch (transid) {
	case KVASER_USB_HYDRA_TRANSID_CANHE:
	case KVASER_USB_HYDRA_TRANSID_CANHE + 1:
	case KVASER_USB_HYDRA_TRANSID_CANHE + 2:
	case KVASER_USB_HYDRA_TRANSID_CANHE + 3:
	case KVASER_USB_HYDRA_TRANSID_CANHE + 4:
		channel = transid & 0x000f;
		he = cmd->map_ch_res.he_addr;
		card_data->channel_to_he[channel] = he;
		break;
	case KVASER_USB_HYDRA_TRANSID_SYSDBG:
		card_data->sysdbg_he = cmd->map_ch_res.he_addr;
		break;
	default:
		dev_warn(&dev->intf->dev,
			 "Unknown CMD_MAP_CHANNEL_RESP transid=0x%x\n",
			 transid);
		break;
	}

	return 0;
}