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
struct usb_pcwd_private {int /*<<< orphan*/  mtx; scalar_t__ exists; } ;
struct usb_interface {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cards_found ; 
 int /*<<< orphan*/  disconnect_mutex ; 
 int /*<<< orphan*/  misc_deregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nowayout ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  unregister_reboot_notifier (int /*<<< orphan*/ *) ; 
 struct usb_pcwd_private* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_pcwd_delete (struct usb_pcwd_private*) ; 
 int /*<<< orphan*/  usb_pcwd_miscdev ; 
 int /*<<< orphan*/  usb_pcwd_notifier ; 
 int /*<<< orphan*/  usb_pcwd_stop (struct usb_pcwd_private*) ; 
 int /*<<< orphan*/  usb_pcwd_temperature_miscdev ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void usb_pcwd_disconnect(struct usb_interface *interface)
{
	struct usb_pcwd_private *usb_pcwd;

	/* prevent races with open() */
	mutex_lock(&disconnect_mutex);

	usb_pcwd = usb_get_intfdata(interface);
	usb_set_intfdata(interface, NULL);

	mutex_lock(&usb_pcwd->mtx);

	/* Stop the timer before we leave */
	if (!nowayout)
		usb_pcwd_stop(usb_pcwd);

	/* We should now stop communicating with the USB PCWD device */
	usb_pcwd->exists = 0;

	/* Deregister */
	misc_deregister(&usb_pcwd_miscdev);
	misc_deregister(&usb_pcwd_temperature_miscdev);
	unregister_reboot_notifier(&usb_pcwd_notifier);

	mutex_unlock(&usb_pcwd->mtx);

	/* Delete the USB PCWD device */
	usb_pcwd_delete(usb_pcwd);

	cards_found--;

	mutex_unlock(&disconnect_mutex);

	pr_info("USB PC Watchdog disconnected\n");
}