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
struct usb_dmac {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  USB_DMAOR ; 
 int /*<<< orphan*/  usb_dmac_write (struct usb_dmac*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void usb_dmac_stop(struct usb_dmac *dmac)
{
	usb_dmac_write(dmac, USB_DMAOR, 0);
}