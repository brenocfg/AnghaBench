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
struct ucan_priv {int /*<<< orphan*/  in_ep_size; int /*<<< orphan*/  udev; } ;

/* Variables and functions */
 int UCAN_MAX_RX_URBS ; 
 int /*<<< orphan*/  memset (struct urb**,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_free_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_urb (struct urb*) ; 
 int /*<<< orphan*/  usb_unanchor_urb (struct urb*) ; 

__attribute__((used)) static void ucan_cleanup_rx_urbs(struct ucan_priv *up, struct urb **urbs)
{
	int i;

	for (i = 0; i < UCAN_MAX_RX_URBS; i++) {
		if (urbs[i]) {
			usb_unanchor_urb(urbs[i]);
			usb_free_coherent(up->udev,
					  up->in_ep_size,
					  urbs[i]->transfer_buffer,
					  urbs[i]->transfer_dma);
			usb_free_urb(urbs[i]);
		}
	}

	memset(urbs, 0, sizeof(*urbs) * UCAN_MAX_RX_URBS);
}