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
struct octeon_hcd {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  octeon_to_hcd (struct octeon_hcd*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_hcd_poll_rh_status (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void octeon_usb_port_callback(struct octeon_hcd *usb)
{
	spin_unlock(&usb->lock);
	usb_hcd_poll_rh_status(octeon_to_hcd(usb));
	spin_lock(&usb->lock);
}