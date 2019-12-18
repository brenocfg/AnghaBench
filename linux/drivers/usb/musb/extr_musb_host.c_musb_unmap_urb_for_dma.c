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
struct usb_hcd {int dummy; } ;
struct urb {int dummy; } ;
struct musb {scalar_t__ hwvers; } ;

/* Variables and functions */
 scalar_t__ MUSB_HWVERS_1800 ; 
 struct musb* hcd_to_musb (struct usb_hcd*) ; 
 int /*<<< orphan*/  musb_free_temp_buffer (struct urb*) ; 
 int /*<<< orphan*/  usb_hcd_unmap_urb_for_dma (struct usb_hcd*,struct urb*) ; 

__attribute__((used)) static void musb_unmap_urb_for_dma(struct usb_hcd *hcd, struct urb *urb)
{
	struct musb	*musb = hcd_to_musb(hcd);

	usb_hcd_unmap_urb_for_dma(hcd, urb);

	/* Do not use this hook for RTL<1.8 (see description above) */
	if (musb->hwvers < MUSB_HWVERS_1800)
		return;

	musb_free_temp_buffer(urb);
}