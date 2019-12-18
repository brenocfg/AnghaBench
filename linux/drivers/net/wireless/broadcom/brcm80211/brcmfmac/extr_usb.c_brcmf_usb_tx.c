#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct device {int dummy; } ;
struct brcmf_usbreq {struct sk_buff* skb; TYPE_2__* urb; struct brcmf_usbdev_info* devinfo; } ;
struct TYPE_4__ {scalar_t__ state; } ;
struct brcmf_usbdev_info {scalar_t__ tx_freecount; scalar_t__ tx_low_watermark; int tx_flowblock; int /*<<< orphan*/  tx_flowblock_lock; int /*<<< orphan*/  tx_freeq; int /*<<< orphan*/  tx_postq; int /*<<< orphan*/  tx_pipe; int /*<<< orphan*/  usbdev; TYPE_1__ bus_pub; } ;
struct TYPE_5__ {int /*<<< orphan*/  transfer_flags; } ;

/* Variables and functions */
 scalar_t__ BRCMFMAC_USB_STATE_UP ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  URB_ZERO_PACKET ; 
 int /*<<< orphan*/  USB ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*,struct sk_buff*) ; 
 int /*<<< orphan*/  brcmf_err (char*) ; 
 int /*<<< orphan*/  brcmf_proto_bcdc_txflowblock (struct device*,int) ; 
 int /*<<< orphan*/  brcmf_usb_del_fromq (struct brcmf_usbdev_info*,struct brcmf_usbreq*) ; 
 struct brcmf_usbreq* brcmf_usb_deq (struct brcmf_usbdev_info*,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  brcmf_usb_enq (struct brcmf_usbdev_info*,int /*<<< orphan*/ *,struct brcmf_usbreq*,scalar_t__*) ; 
 struct brcmf_usbdev_info* brcmf_usb_get_businfo (struct device*) ; 
 int /*<<< orphan*/  brcmf_usb_tx_complete ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct brcmf_usbreq*) ; 
 int usb_submit_urb (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int brcmf_usb_tx(struct device *dev, struct sk_buff *skb)
{
	struct brcmf_usbdev_info *devinfo = brcmf_usb_get_businfo(dev);
	struct brcmf_usbreq  *req;
	int ret;
	unsigned long flags;

	brcmf_dbg(USB, "Enter, skb=%p\n", skb);
	if (devinfo->bus_pub.state != BRCMFMAC_USB_STATE_UP) {
		ret = -EIO;
		goto fail;
	}

	req = brcmf_usb_deq(devinfo, &devinfo->tx_freeq,
					&devinfo->tx_freecount);
	if (!req) {
		brcmf_err("no req to send\n");
		ret = -ENOMEM;
		goto fail;
	}

	req->skb = skb;
	req->devinfo = devinfo;
	usb_fill_bulk_urb(req->urb, devinfo->usbdev, devinfo->tx_pipe,
			  skb->data, skb->len, brcmf_usb_tx_complete, req);
	req->urb->transfer_flags |= URB_ZERO_PACKET;
	brcmf_usb_enq(devinfo, &devinfo->tx_postq, req, NULL);
	ret = usb_submit_urb(req->urb, GFP_ATOMIC);
	if (ret) {
		brcmf_err("brcmf_usb_tx usb_submit_urb FAILED\n");
		brcmf_usb_del_fromq(devinfo, req);
		req->skb = NULL;
		brcmf_usb_enq(devinfo, &devinfo->tx_freeq, req,
			      &devinfo->tx_freecount);
		goto fail;
	}

	spin_lock_irqsave(&devinfo->tx_flowblock_lock, flags);
	if (devinfo->tx_freecount < devinfo->tx_low_watermark &&
	    !devinfo->tx_flowblock) {
		brcmf_proto_bcdc_txflowblock(dev, true);
		devinfo->tx_flowblock = true;
	}
	spin_unlock_irqrestore(&devinfo->tx_flowblock_lock, flags);
	return 0;

fail:
	return ret;
}