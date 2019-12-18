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
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int usb_hcd_map_urb_for_dma (struct usb_hcd*,struct urb*,int /*<<< orphan*/ ) ; 
 scalar_t__ xhci_urb_suitable_for_idt (struct urb*) ; 

__attribute__((used)) static int xhci_map_urb_for_dma(struct usb_hcd *hcd, struct urb *urb,
				gfp_t mem_flags)
{
	if (xhci_urb_suitable_for_idt(urb))
		return 0;

	return usb_hcd_map_urb_for_dma(hcd, urb, mem_flags);
}