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
struct kvaser_usb {int /*<<< orphan*/  nchannels; } ;
struct TYPE_2__ {int /*<<< orphan*/  nchannels; } ;
struct kvaser_cmd {TYPE_1__ card_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_GET_CARD_INFO_REQ ; 
 int /*<<< orphan*/  CMD_GET_CARD_INFO_RESP ; 
 int EINVAL ; 
 int /*<<< orphan*/  KVASER_USB_MAX_NET_DEVICES ; 
 int kvaser_usb_hydra_send_simple_cmd (struct kvaser_usb*,int /*<<< orphan*/ ,int) ; 
 int kvaser_usb_hydra_wait_cmd (struct kvaser_usb*,int /*<<< orphan*/ ,struct kvaser_cmd*) ; 
 int /*<<< orphan*/  memset (struct kvaser_cmd*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int kvaser_usb_hydra_get_card_info(struct kvaser_usb *dev)
{
	struct kvaser_cmd cmd;
	int err;

	err = kvaser_usb_hydra_send_simple_cmd(dev, CMD_GET_CARD_INFO_REQ, -1);
	if (err)
		return err;

	memset(&cmd, 0, sizeof(struct kvaser_cmd));
	err = kvaser_usb_hydra_wait_cmd(dev, CMD_GET_CARD_INFO_RESP, &cmd);
	if (err)
		return err;

	dev->nchannels = cmd.card_info.nchannels;
	if (dev->nchannels > KVASER_USB_MAX_NET_DEVICES)
		return -EINVAL;

	return 0;
}