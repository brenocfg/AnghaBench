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
typedef  int /*<<< orphan*/  usb_complete_t ;
struct urb {scalar_t__ actual_length; } ;
struct rx_agg {int /*<<< orphan*/  list; struct urb* urb; int /*<<< orphan*/  buffer; } ;
struct r8152 {int /*<<< orphan*/  napi; int /*<<< orphan*/  netdev; int /*<<< orphan*/  rx_lock; int /*<<< orphan*/  rx_done; int /*<<< orphan*/  rx_buf_sz; int /*<<< orphan*/  udev; int /*<<< orphan*/  flags; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  RTL8152_UNPLUG ; 
 int /*<<< orphan*/  WORK_ENABLE ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  napi_schedule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_carrier_ok (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_device_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_err (struct r8152*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct rx_agg*,int) ; 
 scalar_t__ read_bulk_callback ; 
 int /*<<< orphan*/  rtl_set_unplug (struct r8152*) ; 
 int /*<<< orphan*/  rx_err ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (struct urb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct rx_agg*) ; 
 int /*<<< orphan*/  usb_rcvbulkpipe (int /*<<< orphan*/ ,int) ; 
 int usb_submit_urb (struct urb*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
int r8152_submit_rx(struct r8152 *tp, struct rx_agg *agg, gfp_t mem_flags)
{
	int ret;

	/* The rx would be stopped, so skip submitting */
	if (test_bit(RTL8152_UNPLUG, &tp->flags) ||
	    !test_bit(WORK_ENABLE, &tp->flags) || !netif_carrier_ok(tp->netdev))
		return 0;

	usb_fill_bulk_urb(agg->urb, tp->udev, usb_rcvbulkpipe(tp->udev, 1),
			  agg->buffer, tp->rx_buf_sz,
			  (usb_complete_t)read_bulk_callback, agg);

	ret = usb_submit_urb(agg->urb, mem_flags);
	if (ret == -ENODEV) {
		rtl_set_unplug(tp);
		netif_device_detach(tp->netdev);
	} else if (ret) {
		struct urb *urb = agg->urb;
		unsigned long flags;

		urb->actual_length = 0;
		spin_lock_irqsave(&tp->rx_lock, flags);
		list_add_tail(&agg->list, &tp->rx_done);
		spin_unlock_irqrestore(&tp->rx_lock, flags);

		netif_err(tp, rx_err, tp->netdev,
			  "Couldn't submit rx[%p], ret = %d\n", agg, ret);

		napi_schedule(&tp->napi);
	}

	return ret;
}