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
struct urb {scalar_t__ status; int /*<<< orphan*/  actual_length; scalar_t__ context; } ;
struct sk_buff {int dummy; } ;
struct brcmf_usbreq {struct sk_buff* skb; struct brcmf_usbdev_info* devinfo; } ;
struct TYPE_2__ {scalar_t__ state; } ;
struct brcmf_usbdev_info {int /*<<< orphan*/  rx_freeq; int /*<<< orphan*/  dev; TYPE_1__ bus_pub; } ;

/* Variables and functions */
 scalar_t__ BRCMFMAC_USB_STATE_UP ; 
 int /*<<< orphan*/  USB ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  brcmf_rx_frame (int /*<<< orphan*/ ,struct sk_buff*,int) ; 
 int /*<<< orphan*/  brcmf_usb_del_fromq (struct brcmf_usbdev_info*,struct brcmf_usbreq*) ; 
 int /*<<< orphan*/  brcmf_usb_enq (struct brcmf_usbdev_info*,int /*<<< orphan*/ *,struct brcmf_usbreq*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  brcmf_usb_rx_refill (struct brcmf_usbdev_info*,struct brcmf_usbreq*) ; 
 int /*<<< orphan*/  brcmu_pkt_buf_free_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void brcmf_usb_rx_complete(struct urb *urb)
{
	struct brcmf_usbreq  *req = (struct brcmf_usbreq *)urb->context;
	struct brcmf_usbdev_info *devinfo = req->devinfo;
	struct sk_buff *skb;

	brcmf_dbg(USB, "Enter, urb->status=%d\n", urb->status);
	brcmf_usb_del_fromq(devinfo, req);
	skb = req->skb;
	req->skb = NULL;

	/* zero length packets indicate usb "failure". Do not refill */
	if (urb->status != 0 || !urb->actual_length) {
		brcmu_pkt_buf_free_skb(skb);
		brcmf_usb_enq(devinfo, &devinfo->rx_freeq, req, NULL);
		return;
	}

	if (devinfo->bus_pub.state == BRCMFMAC_USB_STATE_UP) {
		skb_put(skb, urb->actual_length);
		brcmf_rx_frame(devinfo->dev, skb, true);
		brcmf_usb_rx_refill(devinfo, req);
	} else {
		brcmu_pkt_buf_free_skb(skb);
		brcmf_usb_enq(devinfo, &devinfo->rx_freeq, req, NULL);
	}
	return;

}