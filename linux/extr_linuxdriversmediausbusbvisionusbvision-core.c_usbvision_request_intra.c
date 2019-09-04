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
struct usb_usbvision {int request_intra; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_IRQ ; 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  USBVISION_FORCE_INTRA ; 
 int /*<<< orphan*/  usbvision_write_reg_irq (struct usb_usbvision*,int /*<<< orphan*/ ,unsigned char*,int) ; 

__attribute__((used)) static int usbvision_request_intra(struct usb_usbvision *usbvision)
{
	unsigned char buffer[1];

	PDEBUG(DBG_IRQ, "");
	usbvision->request_intra = 1;
	buffer[0] = 1;
	usbvision_write_reg_irq(usbvision, USBVISION_FORCE_INTRA, buffer, 1);
	return 0;
}