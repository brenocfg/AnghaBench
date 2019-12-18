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
struct synusb {int /*<<< orphan*/  pm_mutex; int /*<<< orphan*/  urb; } ;
typedef  int /*<<< orphan*/  pm_message_t ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct synusb* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int synusb_suspend(struct usb_interface *intf, pm_message_t message)
{
	struct synusb *synusb = usb_get_intfdata(intf);

	mutex_lock(&synusb->pm_mutex);
	usb_kill_urb(synusb->urb);
	mutex_unlock(&synusb->pm_mutex);

	return 0;
}