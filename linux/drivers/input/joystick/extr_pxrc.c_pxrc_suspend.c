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
struct pxrc {int /*<<< orphan*/  pm_mutex; int /*<<< orphan*/  urb; scalar_t__ is_open; } ;
typedef  int /*<<< orphan*/  pm_message_t ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct pxrc* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pxrc_suspend(struct usb_interface *intf, pm_message_t message)
{
	struct pxrc *pxrc = usb_get_intfdata(intf);

	mutex_lock(&pxrc->pm_mutex);
	if (pxrc->is_open)
		usb_kill_urb(pxrc->urb);
	mutex_unlock(&pxrc->pm_mutex);

	return 0;
}