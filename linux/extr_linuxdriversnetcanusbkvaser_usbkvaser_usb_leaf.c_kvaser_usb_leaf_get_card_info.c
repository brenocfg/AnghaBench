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
struct TYPE_8__ {scalar_t__ family; } ;
struct TYPE_5__ {TYPE_4__ leaf; } ;
struct kvaser_usb {int /*<<< orphan*/  nchannels; TYPE_1__ card_data; } ;
struct TYPE_6__ {int /*<<< orphan*/  nchannels; } ;
struct TYPE_7__ {TYPE_2__ cardinfo; } ;
struct kvaser_cmd {TYPE_3__ u; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_GET_CARD_INFO ; 
 int /*<<< orphan*/  CMD_GET_CARD_INFO_REPLY ; 
 int EINVAL ; 
 scalar_t__ KVASER_USBCAN ; 
 int /*<<< orphan*/  KVASER_USB_MAX_NET_DEVICES ; 
 int /*<<< orphan*/  MAX_USBCAN_NET_DEVICES ; 
 int kvaser_usb_leaf_send_simple_cmd (struct kvaser_usb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int kvaser_usb_leaf_wait_cmd (struct kvaser_usb*,int /*<<< orphan*/ ,struct kvaser_cmd*) ; 

__attribute__((used)) static int kvaser_usb_leaf_get_card_info(struct kvaser_usb *dev)
{
	struct kvaser_cmd cmd;
	int err;

	err = kvaser_usb_leaf_send_simple_cmd(dev, CMD_GET_CARD_INFO, 0);
	if (err)
		return err;

	err = kvaser_usb_leaf_wait_cmd(dev, CMD_GET_CARD_INFO_REPLY, &cmd);
	if (err)
		return err;

	dev->nchannels = cmd.u.cardinfo.nchannels;
	if (dev->nchannels > KVASER_USB_MAX_NET_DEVICES ||
	    (dev->card_data.leaf.family == KVASER_USBCAN &&
	     dev->nchannels > MAX_USBCAN_NET_DEVICES))
		return -EINVAL;

	return 0;
}