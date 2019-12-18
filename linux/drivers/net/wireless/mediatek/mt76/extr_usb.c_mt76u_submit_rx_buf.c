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
struct urb {int dummy; } ;
struct mt76_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  MT_EP_IN_PKT_RX ; 
 int /*<<< orphan*/  USB_DIR_IN ; 
 int /*<<< orphan*/  mt76u_complete_rx ; 
 int /*<<< orphan*/  mt76u_fill_bulk_urb (struct mt76_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct urb*,int /*<<< orphan*/ ,struct mt76_dev*) ; 
 int /*<<< orphan*/  trace_submit_urb (struct mt76_dev*,struct urb*) ; 
 int usb_submit_urb (struct urb*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mt76u_submit_rx_buf(struct mt76_dev *dev, struct urb *urb)
{
	mt76u_fill_bulk_urb(dev, USB_DIR_IN, MT_EP_IN_PKT_RX, urb,
			    mt76u_complete_rx, dev);
	trace_submit_urb(dev, urb);

	return usb_submit_urb(urb, GFP_ATOMIC);
}