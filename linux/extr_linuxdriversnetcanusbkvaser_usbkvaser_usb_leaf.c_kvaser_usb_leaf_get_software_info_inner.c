#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int family; } ;
struct TYPE_9__ {TYPE_1__ leaf; } ;
struct kvaser_usb {void* max_tx_urbs; void* fw_version; TYPE_2__ card_data; } ;
struct TYPE_12__ {int /*<<< orphan*/  max_outstanding_tx; int /*<<< orphan*/  fw_version; } ;
struct TYPE_13__ {TYPE_5__ softinfo; } ;
struct TYPE_10__ {int /*<<< orphan*/  max_outstanding_tx; int /*<<< orphan*/  fw_version; } ;
struct TYPE_11__ {TYPE_3__ softinfo; } ;
struct TYPE_14__ {TYPE_6__ usbcan; TYPE_4__ leaf; } ;
struct kvaser_cmd {TYPE_7__ u; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_GET_SOFTWARE_INFO ; 
 int /*<<< orphan*/  CMD_GET_SOFTWARE_INFO_REPLY ; 
#define  KVASER_LEAF 129 
#define  KVASER_USBCAN 128 
 int kvaser_usb_leaf_send_simple_cmd (struct kvaser_usb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int kvaser_usb_leaf_wait_cmd (struct kvaser_usb*,int /*<<< orphan*/ ,struct kvaser_cmd*) ; 
 void* le16_to_cpu (int /*<<< orphan*/ ) ; 
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int kvaser_usb_leaf_get_software_info_inner(struct kvaser_usb *dev)
{
	struct kvaser_cmd cmd;
	int err;

	err = kvaser_usb_leaf_send_simple_cmd(dev, CMD_GET_SOFTWARE_INFO, 0);
	if (err)
		return err;

	err = kvaser_usb_leaf_wait_cmd(dev, CMD_GET_SOFTWARE_INFO_REPLY, &cmd);
	if (err)
		return err;

	switch (dev->card_data.leaf.family) {
	case KVASER_LEAF:
		dev->fw_version = le32_to_cpu(cmd.u.leaf.softinfo.fw_version);
		dev->max_tx_urbs =
			le16_to_cpu(cmd.u.leaf.softinfo.max_outstanding_tx);
		break;
	case KVASER_USBCAN:
		dev->fw_version = le32_to_cpu(cmd.u.usbcan.softinfo.fw_version);
		dev->max_tx_urbs =
			le16_to_cpu(cmd.u.usbcan.softinfo.max_outstanding_tx);
		break;
	}

	return 0;
}