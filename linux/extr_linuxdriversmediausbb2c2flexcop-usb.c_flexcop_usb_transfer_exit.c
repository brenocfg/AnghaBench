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
struct flexcop_usb {int /*<<< orphan*/  dma_addr; int /*<<< orphan*/ * iso_buffer; int /*<<< orphan*/  buffer_size; int /*<<< orphan*/  udev; int /*<<< orphan*/ ** iso_urb; } ;

/* Variables and functions */
 int B2C2_USB_NUM_ISO_URB ; 
 int /*<<< orphan*/  deb_ts (char*,int) ; 
 int /*<<< orphan*/  usb_free_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_urb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void flexcop_usb_transfer_exit(struct flexcop_usb *fc_usb)
{
	int i;
	for (i = 0; i < B2C2_USB_NUM_ISO_URB; i++)
		if (fc_usb->iso_urb[i] != NULL) {
			deb_ts("unlinking/killing urb no. %d\n",i);
			usb_kill_urb(fc_usb->iso_urb[i]);
			usb_free_urb(fc_usb->iso_urb[i]);
		}

	if (fc_usb->iso_buffer != NULL)
		usb_free_coherent(fc_usb->udev,
			fc_usb->buffer_size, fc_usb->iso_buffer,
			fc_usb->dma_addr);
}