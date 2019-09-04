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
struct urb {struct pcan_usb* context; } ;
struct pcan_usb {int /*<<< orphan*/  restart_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCAN_USB_STARTUP_TIMEOUT ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  peak_usb_async_complete (struct urb*) ; 

__attribute__((used)) static void pcan_usb_restart_pending(struct urb *urb)
{
	struct pcan_usb *pdev = urb->context;

	/* the PCAN-USB needs time to restart */
	mod_timer(&pdev->restart_timer,
			jiffies + msecs_to_jiffies(PCAN_USB_STARTUP_TIMEOUT));

	/* can delete usb resources */
	peak_usb_async_complete(urb);
}