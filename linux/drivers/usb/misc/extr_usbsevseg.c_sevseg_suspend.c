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
struct usb_sevsegdev {scalar_t__ shadow_power; } ;
struct usb_interface {int dummy; } ;
typedef  int /*<<< orphan*/  pm_message_t ;

/* Variables and functions */
 struct usb_sevsegdev* usb_get_intfdata (struct usb_interface*) ; 

__attribute__((used)) static int sevseg_suspend(struct usb_interface *intf, pm_message_t message)
{
	struct usb_sevsegdev *mydev;

	mydev = usb_get_intfdata(intf);
	mydev->shadow_power = 0;

	return 0;
}