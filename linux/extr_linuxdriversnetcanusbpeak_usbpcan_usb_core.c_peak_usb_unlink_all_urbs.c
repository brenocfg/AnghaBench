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
struct urb {int dummy; } ;
struct peak_usb_device {int /*<<< orphan*/  active_tx_urbs; int /*<<< orphan*/  tx_submitted; TYPE_1__* tx_contexts; int /*<<< orphan*/  rx_submitted; } ;
struct TYPE_2__ {int echo_index; struct urb* urb; } ;

/* Variables and functions */
 int PCAN_USB_MAX_TX_URBS ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_urb (struct urb*) ; 
 int /*<<< orphan*/  usb_kill_anchored_urbs (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void peak_usb_unlink_all_urbs(struct peak_usb_device *dev)
{
	int i;

	/* free all Rx (submitted) urbs */
	usb_kill_anchored_urbs(&dev->rx_submitted);

	/* free unsubmitted Tx urbs first */
	for (i = 0; i < PCAN_USB_MAX_TX_URBS; i++) {
		struct urb *urb = dev->tx_contexts[i].urb;

		if (!urb ||
		    dev->tx_contexts[i].echo_index != PCAN_USB_MAX_TX_URBS) {
			/*
			 * this urb is already released or always submitted,
			 * let usb core free by itself
			 */
			continue;
		}

		usb_free_urb(urb);
		dev->tx_contexts[i].urb = NULL;
	}

	/* then free all submitted Tx urbs */
	usb_kill_anchored_urbs(&dev->tx_submitted);
	atomic_set(&dev->active_tx_urbs, 0);
}