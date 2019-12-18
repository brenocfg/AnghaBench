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
struct usb_hcd {TYPE_1__* driver; } ;
struct urb {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* unmap_urb_for_dma ) (struct usb_hcd*,struct urb*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct usb_hcd*,struct urb*) ; 
 int /*<<< orphan*/  usb_hcd_unmap_urb_for_dma (struct usb_hcd*,struct urb*) ; 

__attribute__((used)) static void unmap_urb_for_dma(struct usb_hcd *hcd, struct urb *urb)
{
	if (hcd->driver->unmap_urb_for_dma)
		hcd->driver->unmap_urb_for_dma(hcd, urb);
	else
		usb_hcd_unmap_urb_for_dma(hcd, urb);
}