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
struct ci_hdrc {int /*<<< orphan*/  gadget; scalar_t__ vbus_active; int /*<<< orphan*/  is_otg; } ;

/* Variables and functions */
 int /*<<< orphan*/  OTGSC_BSV ; 
 scalar_t__ hw_read_otgsc (struct ci_hdrc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_gadget_vbus_connect (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_gadget_vbus_disconnect (int /*<<< orphan*/ *) ; 

void ci_handle_vbus_change(struct ci_hdrc *ci)
{
	if (!ci->is_otg)
		return;

	if (hw_read_otgsc(ci, OTGSC_BSV) && !ci->vbus_active)
		usb_gadget_vbus_connect(&ci->gadget);
	else if (!hw_read_otgsc(ci, OTGSC_BSV) && ci->vbus_active)
		usb_gadget_vbus_disconnect(&ci->gadget);
}