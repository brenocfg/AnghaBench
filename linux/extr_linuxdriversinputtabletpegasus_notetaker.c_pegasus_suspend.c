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
struct pegasus {int /*<<< orphan*/  pm_mutex; int /*<<< orphan*/  init; int /*<<< orphan*/  irq; } ;
typedef  int /*<<< orphan*/  pm_message_t ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct pegasus* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pegasus_suspend(struct usb_interface *intf, pm_message_t message)
{
	struct pegasus *pegasus = usb_get_intfdata(intf);

	mutex_lock(&pegasus->pm_mutex);
	usb_kill_urb(pegasus->irq);
	cancel_work_sync(&pegasus->init);
	mutex_unlock(&pegasus->pm_mutex);

	return 0;
}