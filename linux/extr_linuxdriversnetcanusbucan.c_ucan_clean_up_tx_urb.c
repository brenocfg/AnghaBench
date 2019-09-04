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
struct urb {int /*<<< orphan*/  transfer_dma; int /*<<< orphan*/  transfer_buffer; } ;
struct ucan_priv {int /*<<< orphan*/  udev; } ;
struct ucan_message_out {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  usb_free_coherent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_urb (struct urb*) ; 

__attribute__((used)) static void ucan_clean_up_tx_urb(struct ucan_priv *up, struct urb *urb)
{
	usb_free_coherent(up->udev, sizeof(struct ucan_message_out),
			  urb->transfer_buffer, urb->transfer_dma);
	usb_free_urb(urb);
}