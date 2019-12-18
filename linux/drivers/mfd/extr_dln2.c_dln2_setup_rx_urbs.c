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
struct usb_host_interface {int dummy; } ;
struct dln2_dev {int /*<<< orphan*/ * rx_buf; int /*<<< orphan*/  ep_in; int /*<<< orphan*/  usb_dev; int /*<<< orphan*/ * rx_urb; } ;

/* Variables and functions */
 int DLN2_MAX_URBS ; 
 int DLN2_RX_BUF_SIZE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dln2_rx ; 
 int /*<<< orphan*/  kmalloc (int const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int const,int /*<<< orphan*/ ,struct dln2_dev*) ; 
 int /*<<< orphan*/  usb_rcvbulkpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dln2_setup_rx_urbs(struct dln2_dev *dln2,
			      struct usb_host_interface *hostif)
{
	int i;
	const int rx_max_size = DLN2_RX_BUF_SIZE;

	for (i = 0; i < DLN2_MAX_URBS; i++) {
		dln2->rx_buf[i] = kmalloc(rx_max_size, GFP_KERNEL);
		if (!dln2->rx_buf[i])
			return -ENOMEM;

		dln2->rx_urb[i] = usb_alloc_urb(0, GFP_KERNEL);
		if (!dln2->rx_urb[i])
			return -ENOMEM;

		usb_fill_bulk_urb(dln2->rx_urb[i], dln2->usb_dev,
				  usb_rcvbulkpipe(dln2->usb_dev, dln2->ep_in),
				  dln2->rx_buf[i], rx_max_size, dln2_rx, dln2);
	}

	return 0;
}