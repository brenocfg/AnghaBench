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
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct can_bittiming {scalar_t__ brp; scalar_t__ sjw; scalar_t__ phase_seg2; scalar_t__ phase_seg1; scalar_t__ prop_seg; } ;
struct TYPE_2__ {int ctrlmode; struct can_bittiming bittiming; } ;
struct usb_8dev_priv {TYPE_1__ can; } ;
struct usb_8dev_cmd_msg {scalar_t__* data; int /*<<< orphan*/  opt1; int /*<<< orphan*/  command; } ;
typedef  int /*<<< orphan*/  outmsg ;
typedef  int /*<<< orphan*/  beflags ;
typedef  int /*<<< orphan*/  bebrp ;
typedef  int /*<<< orphan*/  __be32 ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int CAN_CTRLMODE_LISTENONLY ; 
 int CAN_CTRLMODE_LOOPBACK ; 
 int CAN_CTRLMODE_ONE_SHOT ; 
 int /*<<< orphan*/  USB_8DEV_BAUD_MANUAL ; 
 int USB_8DEV_DISABLE_AUTO_RESTRANS ; 
 int USB_8DEV_LOOPBACK ; 
 int /*<<< orphan*/  USB_8DEV_OPEN ; 
 int USB_8DEV_SILENT ; 
 int USB_8DEV_STATUS_FRAME ; 
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (struct usb_8dev_cmd_msg*,int /*<<< orphan*/ ,int) ; 
 int usb_8dev_send_cmd (struct usb_8dev_priv*,struct usb_8dev_cmd_msg*,struct usb_8dev_cmd_msg*) ; 

__attribute__((used)) static int usb_8dev_cmd_open(struct usb_8dev_priv *priv)
{
	struct can_bittiming *bt = &priv->can.bittiming;
	struct usb_8dev_cmd_msg outmsg;
	struct usb_8dev_cmd_msg inmsg;
	u32 ctrlmode = priv->can.ctrlmode;
	u32 flags = USB_8DEV_STATUS_FRAME;
	__be32 beflags;
	__be16 bebrp;

	memset(&outmsg, 0, sizeof(outmsg));
	outmsg.command = USB_8DEV_OPEN;
	outmsg.opt1 = USB_8DEV_BAUD_MANUAL;
	outmsg.data[0] = bt->prop_seg + bt->phase_seg1;
	outmsg.data[1] = bt->phase_seg2;
	outmsg.data[2] = bt->sjw;

	/* BRP */
	bebrp = cpu_to_be16((u16)bt->brp);
	memcpy(&outmsg.data[3], &bebrp, sizeof(bebrp));

	/* flags */
	if (ctrlmode & CAN_CTRLMODE_LOOPBACK)
		flags |= USB_8DEV_LOOPBACK;
	if (ctrlmode & CAN_CTRLMODE_LISTENONLY)
		flags |= USB_8DEV_SILENT;
	if (ctrlmode & CAN_CTRLMODE_ONE_SHOT)
		flags |= USB_8DEV_DISABLE_AUTO_RESTRANS;

	beflags = cpu_to_be32(flags);
	memcpy(&outmsg.data[5], &beflags, sizeof(beflags));

	return usb_8dev_send_cmd(priv, &outmsg, &inmsg);
}