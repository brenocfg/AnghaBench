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
struct usb_interface {int dummy; } ;
struct ttusbir {int /*<<< orphan*/  bulk_urb; int /*<<< orphan*/  led; int /*<<< orphan*/ * urb; } ;
typedef  int /*<<< orphan*/  pm_message_t ;

/* Variables and functions */
 int NUM_URBS ; 
 int /*<<< orphan*/  led_classdev_suspend (int /*<<< orphan*/ *) ; 
 struct ttusbir* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ttusbir_suspend(struct usb_interface *intf, pm_message_t message)
{
	struct ttusbir *tt = usb_get_intfdata(intf);
	int i;

	for (i = 0; i < NUM_URBS; i++)
		usb_kill_urb(tt->urb[i]);

	led_classdev_suspend(&tt->led);
	usb_kill_urb(tt->bulk_urb);

	return 0;
}