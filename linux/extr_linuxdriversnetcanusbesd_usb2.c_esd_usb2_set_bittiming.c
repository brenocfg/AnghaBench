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
typedef  int u32 ;
struct net_device {int dummy; } ;
struct can_bittiming {int brp; int sjw; int prop_seg; int phase_seg1; int phase_seg2; } ;
struct TYPE_10__ {int ctrlmode; struct can_bittiming bittiming; } ;
struct esd_usb2_net_priv {TYPE_7__* usb2; int /*<<< orphan*/  index; TYPE_3__ can; } ;
struct TYPE_12__ {int /*<<< orphan*/  baud; scalar_t__ rsvd; int /*<<< orphan*/  net; } ;
struct TYPE_11__ {int len; int /*<<< orphan*/  cmd; } ;
struct TYPE_13__ {TYPE_5__ setbaud; TYPE_4__ hdr; } ;
struct esd_usb2_msg {TYPE_6__ msg; } ;
struct TYPE_14__ {TYPE_2__* udev; } ;
struct TYPE_8__ {int /*<<< orphan*/  idProduct; } ;
struct TYPE_9__ {TYPE_1__ descriptor; } ;

/* Variables and functions */
 int CAN_CTRLMODE_3_SAMPLES ; 
 int CAN_CTRLMODE_LISTENONLY ; 
 int /*<<< orphan*/  CMD_SETBAUD ; 
 int ENOMEM ; 
 int ESD_USB2_3_SAMPLES ; 
 int ESD_USB2_BRP_MAX ; 
 int ESD_USB2_LOM ; 
 int ESD_USB2_SJW_MAX ; 
 int ESD_USB2_SJW_SHIFT ; 
 int ESD_USB2_TSEG1_MAX ; 
 int ESD_USB2_TSEG1_SHIFT ; 
 int ESD_USB2_TSEG2_MAX ; 
 int ESD_USB2_TSEG2_SHIFT ; 
 int ESD_USB2_UBR ; 
 int ESD_USBM_SJW_SHIFT ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ USB_CANUSBM_PRODUCT_ID ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int esd_usb2_send_msg (TYPE_7__*,struct esd_usb2_msg*) ; 
 int /*<<< orphan*/  kfree (struct esd_usb2_msg*) ; 
 struct esd_usb2_msg* kmalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*,int) ; 
 struct esd_usb2_net_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int esd_usb2_set_bittiming(struct net_device *netdev)
{
	struct esd_usb2_net_priv *priv = netdev_priv(netdev);
	struct can_bittiming *bt = &priv->can.bittiming;
	struct esd_usb2_msg *msg;
	int err;
	u32 canbtr;
	int sjw_shift;

	canbtr = ESD_USB2_UBR;
	if (priv->can.ctrlmode & CAN_CTRLMODE_LISTENONLY)
		canbtr |= ESD_USB2_LOM;

	canbtr |= (bt->brp - 1) & (ESD_USB2_BRP_MAX - 1);

	if (le16_to_cpu(priv->usb2->udev->descriptor.idProduct) ==
	    USB_CANUSBM_PRODUCT_ID)
		sjw_shift = ESD_USBM_SJW_SHIFT;
	else
		sjw_shift = ESD_USB2_SJW_SHIFT;

	canbtr |= ((bt->sjw - 1) & (ESD_USB2_SJW_MAX - 1))
		<< sjw_shift;
	canbtr |= ((bt->prop_seg + bt->phase_seg1 - 1)
		   & (ESD_USB2_TSEG1_MAX - 1))
		<< ESD_USB2_TSEG1_SHIFT;
	canbtr |= ((bt->phase_seg2 - 1) & (ESD_USB2_TSEG2_MAX - 1))
		<< ESD_USB2_TSEG2_SHIFT;
	if (priv->can.ctrlmode & CAN_CTRLMODE_3_SAMPLES)
		canbtr |= ESD_USB2_3_SAMPLES;

	msg = kmalloc(sizeof(*msg), GFP_KERNEL);
	if (!msg)
		return -ENOMEM;

	msg->msg.hdr.len = 2;
	msg->msg.hdr.cmd = CMD_SETBAUD;
	msg->msg.setbaud.net = priv->index;
	msg->msg.setbaud.rsvd = 0;
	msg->msg.setbaud.baud = cpu_to_le32(canbtr);

	netdev_info(netdev, "setting BTR=%#x\n", canbtr);

	err = esd_usb2_send_msg(priv->usb2, msg);

	kfree(msg);
	return err;
}