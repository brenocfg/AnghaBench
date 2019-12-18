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
struct urb {int /*<<< orphan*/  transfer_flags; int /*<<< orphan*/  transfer_dma; } ;
struct ucan_priv {int /*<<< orphan*/  rx_urbs; int /*<<< orphan*/  in_ep_size; int /*<<< orphan*/  in_ep_addr; int /*<<< orphan*/  udev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int UCAN_MAX_RX_URBS ; 
 int /*<<< orphan*/  URB_NO_TRANSFER_DMA_MAP ; 
 int /*<<< orphan*/  memset (struct urb**,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ucan_cleanup_rx_urbs (struct ucan_priv*,struct urb**) ; 
 int /*<<< orphan*/  ucan_read_bulk_callback ; 
 void* usb_alloc_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct urb* usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_anchor_urb (struct urb*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (struct urb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ucan_priv*) ; 
 int /*<<< orphan*/  usb_free_urb (struct urb*) ; 
 int /*<<< orphan*/  usb_rcvbulkpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ucan_prepare_and_anchor_rx_urbs(struct ucan_priv *up,
					   struct urb **urbs)
{
	int i;

	memset(urbs, 0, sizeof(*urbs) * UCAN_MAX_RX_URBS);

	for (i = 0; i < UCAN_MAX_RX_URBS; i++) {
		void *buf;

		urbs[i] = usb_alloc_urb(0, GFP_KERNEL);
		if (!urbs[i])
			goto err;

		buf = usb_alloc_coherent(up->udev,
					 up->in_ep_size,
					 GFP_KERNEL, &urbs[i]->transfer_dma);
		if (!buf) {
			/* cleanup this urb */
			usb_free_urb(urbs[i]);
			urbs[i] = NULL;
			goto err;
		}

		usb_fill_bulk_urb(urbs[i], up->udev,
				  usb_rcvbulkpipe(up->udev,
						  up->in_ep_addr),
				  buf,
				  up->in_ep_size,
				  ucan_read_bulk_callback,
				  up);

		urbs[i]->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;

		usb_anchor_urb(urbs[i], &up->rx_urbs);
	}
	return 0;

err:
	/* cleanup other unsubmitted urbs */
	ucan_cleanup_rx_urbs(up, urbs);
	return -ENOMEM;
}