#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  usb_complete_t ;
struct usb_device {int dummy; } ;
struct mt7601u_dma_buf {TYPE_1__* urb; int /*<<< orphan*/  dma; int /*<<< orphan*/  len; int /*<<< orphan*/  buf; } ;
struct mt7601u_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/ * out_eps; int /*<<< orphan*/ * in_eps; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_4__ {int /*<<< orphan*/  transfer_flags; int /*<<< orphan*/  transfer_dma; } ;

/* Variables and functions */
 int /*<<< orphan*/  URB_NO_TRANSFER_DMA_MAP ; 
 int USB_DIR_IN ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,int,int) ; 
 struct usb_device* mt7601u_to_usb_dev (struct mt7601u_dev*) ; 
 int /*<<< orphan*/  trace_mt_submit_urb (struct mt7601u_dev*,TYPE_1__*) ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (TYPE_1__*,struct usb_device*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 unsigned int usb_rcvbulkpipe (struct usb_device*,int /*<<< orphan*/ ) ; 
 unsigned int usb_sndbulkpipe (struct usb_device*,int /*<<< orphan*/ ) ; 
 int usb_submit_urb (TYPE_1__*,int /*<<< orphan*/ ) ; 

int mt7601u_usb_submit_buf(struct mt7601u_dev *dev, int dir, int ep_idx,
			   struct mt7601u_dma_buf *buf, gfp_t gfp,
			   usb_complete_t complete_fn, void *context)
{
	struct usb_device *usb_dev = mt7601u_to_usb_dev(dev);
	unsigned pipe;
	int ret;

	if (dir == USB_DIR_IN)
		pipe = usb_rcvbulkpipe(usb_dev, dev->in_eps[ep_idx]);
	else
		pipe = usb_sndbulkpipe(usb_dev, dev->out_eps[ep_idx]);

	usb_fill_bulk_urb(buf->urb, usb_dev, pipe, buf->buf, buf->len,
			  complete_fn, context);
	buf->urb->transfer_dma = buf->dma;
	buf->urb->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;

	trace_mt_submit_urb(dev, buf->urb);
	ret = usb_submit_urb(buf->urb, gfp);
	if (ret)
		dev_err(dev->dev, "Error: submit URB dir:%d ep:%d failed:%d\n",
			dir, ep_idx, ret);
	return ret;
}