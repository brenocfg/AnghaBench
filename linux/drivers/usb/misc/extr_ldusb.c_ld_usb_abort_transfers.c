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
struct ld_usb {int /*<<< orphan*/  interrupt_out_urb; scalar_t__ interrupt_out_busy; int /*<<< orphan*/  interrupt_in_urb; scalar_t__ interrupt_in_running; } ;

/* Variables and functions */
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ld_usb_abort_transfers(struct ld_usb *dev)
{
	/* shutdown transfer */
	if (dev->interrupt_in_running) {
		dev->interrupt_in_running = 0;
		usb_kill_urb(dev->interrupt_in_urb);
	}
	if (dev->interrupt_out_busy)
		usb_kill_urb(dev->interrupt_out_urb);
}