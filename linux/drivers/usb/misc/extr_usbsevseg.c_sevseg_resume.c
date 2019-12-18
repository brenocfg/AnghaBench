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
struct usb_sevsegdev {int shadow_power; } ;
struct usb_interface {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOIO ; 
 int /*<<< orphan*/  update_display_mode (struct usb_sevsegdev*) ; 
 int /*<<< orphan*/  update_display_visual (struct usb_sevsegdev*,int /*<<< orphan*/ ) ; 
 struct usb_sevsegdev* usb_get_intfdata (struct usb_interface*) ; 

__attribute__((used)) static int sevseg_resume(struct usb_interface *intf)
{
	struct usb_sevsegdev *mydev;

	mydev = usb_get_intfdata(intf);
	mydev->shadow_power = 1;
	update_display_mode(mydev);
	update_display_visual(mydev, GFP_NOIO);

	return 0;
}