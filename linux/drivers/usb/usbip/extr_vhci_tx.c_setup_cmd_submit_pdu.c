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
struct vhci_priv {int /*<<< orphan*/  seqnum; struct vhci_device* vdev; } ;
struct vhci_device {int /*<<< orphan*/  devid; } ;
struct TYPE_5__ {int /*<<< orphan*/  setup; } ;
struct TYPE_6__ {TYPE_2__ cmd_submit; } ;
struct TYPE_4__ {int /*<<< orphan*/  ep; int /*<<< orphan*/  direction; int /*<<< orphan*/  devid; int /*<<< orphan*/  seqnum; int /*<<< orphan*/  command; } ;
struct usbip_header {TYPE_3__ u; TYPE_1__ base; } ;
struct urb {scalar_t__ setup_packet; int /*<<< orphan*/  pipe; scalar_t__ hcpriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  USBIP_CMD_SUBMIT ; 
 int /*<<< orphan*/  USBIP_DIR_IN ; 
 int /*<<< orphan*/  USBIP_DIR_OUT ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  usb_pipedevice (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_pipeendpoint (int /*<<< orphan*/ ) ; 
 scalar_t__ usb_pipein (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbip_dbg_vhci_tx (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbip_pack_pdu (struct usbip_header*,struct urb*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void setup_cmd_submit_pdu(struct usbip_header *pdup,  struct urb *urb)
{
	struct vhci_priv *priv = ((struct vhci_priv *)urb->hcpriv);
	struct vhci_device *vdev = priv->vdev;

	usbip_dbg_vhci_tx("URB, local devnum %u, remote devid %u\n",
			  usb_pipedevice(urb->pipe), vdev->devid);

	pdup->base.command   = USBIP_CMD_SUBMIT;
	pdup->base.seqnum    = priv->seqnum;
	pdup->base.devid     = vdev->devid;
	pdup->base.direction = usb_pipein(urb->pipe) ?
		USBIP_DIR_IN : USBIP_DIR_OUT;
	pdup->base.ep	     = usb_pipeendpoint(urb->pipe);

	usbip_pack_pdu(pdup, urb, USBIP_CMD_SUBMIT, 1);

	if (urb->setup_packet)
		memcpy(pdup->u.cmd_submit.setup, urb->setup_packet, 8);
}