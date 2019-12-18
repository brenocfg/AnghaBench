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
struct renesas_usb3 {scalar_t__ connection_state; int /*<<< orphan*/  extcon_work; int /*<<< orphan*/  forced_b_device; scalar_t__ extcon_host; int /*<<< orphan*/  role_sw_by_connector; } ;

/* Variables and functions */
 scalar_t__ USB_ROLE_HOST ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 scalar_t__ usb3_is_a_device (struct renesas_usb3*) ; 
 int /*<<< orphan*/  usb3_mode_config (struct renesas_usb3*,int,int) ; 

__attribute__((used)) static void usb3_check_id(struct renesas_usb3 *usb3)
{
	usb3->extcon_host = usb3_is_a_device(usb3);

	if ((!usb3->role_sw_by_connector && usb3->extcon_host &&
	     !usb3->forced_b_device) || usb3->connection_state == USB_ROLE_HOST)
		usb3_mode_config(usb3, true, true);
	else
		usb3_mode_config(usb3, false, false);

	schedule_work(&usb3->extcon_work);
}