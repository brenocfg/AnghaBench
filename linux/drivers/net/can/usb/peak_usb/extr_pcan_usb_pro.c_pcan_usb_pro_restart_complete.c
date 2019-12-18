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
struct urb {int /*<<< orphan*/  context; } ;

/* Variables and functions */
 int /*<<< orphan*/  peak_usb_async_complete (struct urb*) ; 
 int /*<<< orphan*/  peak_usb_restart_complete (int /*<<< orphan*/ ) ; 

void pcan_usb_pro_restart_complete(struct urb *urb)
{
	/* can delete usb resources */
	peak_usb_async_complete(urb);

	/* notify candev and netdev */
	peak_usb_restart_complete(urb->context);
}