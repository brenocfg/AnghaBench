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
typedef  int u16 ;
struct go7007_usb {TYPE_1__* board; } ;
struct go7007 {scalar_t__ status; int /*<<< orphan*/  dev; struct go7007_usb* hpi_context; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int GO7007_USB_EZUSB ; 
 scalar_t__ STATUS_SHUTDOWN ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ go7007_read_interrupt (struct go7007*,int*,int*) ; 
 scalar_t__ go7007_usb_vendor_request (struct go7007*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ go7007_write_interrupt (struct go7007*,int,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 

__attribute__((used)) static int go7007_usb_interface_reset(struct go7007 *go)
{
	struct go7007_usb *usb = go->hpi_context;
	u16 intr_val, intr_data;

	if (go->status == STATUS_SHUTDOWN)
		return -1;
	/* Reset encoder */
	if (go7007_write_interrupt(go, 0x0001, 0x0001) < 0)
		return -1;
	msleep(100);

	if (usb->board->flags & GO7007_USB_EZUSB) {
		/* Reset buffer in EZ-USB */
		pr_debug("resetting EZ-USB buffers\n");
		if (go7007_usb_vendor_request(go, 0x10, 0, 0, NULL, 0, 0) < 0 ||
		    go7007_usb_vendor_request(go, 0x10, 0, 0, NULL, 0, 0) < 0)
			return -1;

		/* Reset encoder again */
		if (go7007_write_interrupt(go, 0x0001, 0x0001) < 0)
			return -1;
		msleep(100);
	}

	/* Wait for an interrupt to indicate successful hardware reset */
	if (go7007_read_interrupt(go, &intr_val, &intr_data) < 0 ||
			(intr_val & ~0x1) != 0x55aa) {
		dev_err(go->dev, "unable to reset the USB interface\n");
		return -1;
	}
	return 0;
}