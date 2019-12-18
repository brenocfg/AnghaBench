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
struct musb {scalar_t__ port_mode; int /*<<< orphan*/  g; int /*<<< orphan*/  gadget_work; } ;

/* Variables and functions */
 scalar_t__ MUSB_HOST ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_del_gadget_udc (int /*<<< orphan*/ *) ; 

void musb_gadget_cleanup(struct musb *musb)
{
	if (musb->port_mode == MUSB_HOST)
		return;

	cancel_delayed_work_sync(&musb->gadget_work);
	usb_del_gadget_udc(&musb->g);
}