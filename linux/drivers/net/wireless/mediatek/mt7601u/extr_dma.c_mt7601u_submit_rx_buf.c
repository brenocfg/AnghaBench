#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct usb_device {int dummy; } ;
struct mt7601u_dma_buf_rx {int /*<<< orphan*/  urb; int /*<<< orphan*/  p; } ;
struct mt7601u_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/ * in_eps; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 size_t MT_EP_IN_PKT_RX ; 
 int /*<<< orphan*/  MT_RX_URB_SIZE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  mt7601u_complete_rx ; 
 struct usb_device* mt7601u_to_usb_dev (struct mt7601u_dev*) ; 
 int /*<<< orphan*/ * page_address (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_mt_submit_urb (struct mt7601u_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (int /*<<< orphan*/ ,struct usb_device*,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mt7601u_dev*) ; 
 unsigned int usb_rcvbulkpipe (struct usb_device*,int /*<<< orphan*/ ) ; 
 int usb_submit_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mt7601u_submit_rx_buf(struct mt7601u_dev *dev,
				 struct mt7601u_dma_buf_rx *e, gfp_t gfp)
{
	struct usb_device *usb_dev = mt7601u_to_usb_dev(dev);
	u8 *buf = page_address(e->p);
	unsigned pipe;
	int ret;

	pipe = usb_rcvbulkpipe(usb_dev, dev->in_eps[MT_EP_IN_PKT_RX]);

	usb_fill_bulk_urb(e->urb, usb_dev, pipe, buf, MT_RX_URB_SIZE,
			  mt7601u_complete_rx, dev);

	trace_mt_submit_urb(dev, e->urb);
	ret = usb_submit_urb(e->urb, gfp);
	if (ret)
		dev_err(dev->dev, "Error: submit RX URB failed:%d\n", ret);

	return ret;
}