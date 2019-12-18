#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct catc {int tx_ptr; size_t tx_idx; int /*<<< orphan*/  netdev; TYPE_1__* usbdev; TYPE_2__* tx_urb; int /*<<< orphan*/ * tx_buf; scalar_t__ is_f5u011; } ;
struct TYPE_4__ {int transfer_buffer_length; TYPE_1__* dev; int /*<<< orphan*/  transfer_buffer; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  netif_trans_update (int /*<<< orphan*/ ) ; 
 int usb_submit_urb (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int catc_tx_run(struct catc *catc)
{
	int status;

	if (catc->is_f5u011)
		catc->tx_ptr = (catc->tx_ptr + 63) & ~63;

	catc->tx_urb->transfer_buffer_length = catc->tx_ptr;
	catc->tx_urb->transfer_buffer = catc->tx_buf[catc->tx_idx];
	catc->tx_urb->dev = catc->usbdev;

	if ((status = usb_submit_urb(catc->tx_urb, GFP_ATOMIC)) < 0)
		dev_err(&catc->usbdev->dev, "submit(tx_urb), status %d\n",
			status);

	catc->tx_idx = !catc->tx_idx;
	catc->tx_ptr = 0;

	netif_trans_update(catc->netdev);
	return status;
}