#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vnt_rcb {int in_use; int /*<<< orphan*/  skb; struct urb* urb; } ;
struct vnt_private {TYPE_1__* usb; } ;
struct urb {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  MAX_TOTAL_SIZE_WITH_ALL_HEADERS ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  skb_put (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_tailroom (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (struct urb*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vnt_rcb*) ; 
 int /*<<< orphan*/  usb_rcvbulkpipe (TYPE_1__*,int) ; 
 int usb_submit_urb (struct urb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnt_submit_rx_urb_complete ; 

int vnt_submit_rx_urb(struct vnt_private *priv, struct vnt_rcb *rcb)
{
	int ret = 0;
	struct urb *urb = rcb->urb;

	if (!rcb->skb) {
		dev_dbg(&priv->usb->dev, "rcb->skb is null\n");
		ret = -EINVAL;
		goto end;
	}

	usb_fill_bulk_urb(urb,
			  priv->usb,
			  usb_rcvbulkpipe(priv->usb, 2),
			  skb_put(rcb->skb, skb_tailroom(rcb->skb)),
			  MAX_TOTAL_SIZE_WITH_ALL_HEADERS,
			  vnt_submit_rx_urb_complete,
			  rcb);

	ret = usb_submit_urb(urb, GFP_ATOMIC);
	if (ret) {
		dev_dbg(&priv->usb->dev, "Submit Rx URB failed %d\n", ret);
		goto end;
	}

	rcb->in_use = true;

end:
	return ret;
}