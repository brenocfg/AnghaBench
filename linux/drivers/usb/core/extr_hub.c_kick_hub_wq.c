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
struct usb_hub {int /*<<< orphan*/  kref; int /*<<< orphan*/  events; int /*<<< orphan*/  intfdev; scalar_t__ disconnected; } ;

/* Variables and functions */
 int /*<<< orphan*/  hub_release ; 
 int /*<<< orphan*/  hub_wq ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct usb_interface* to_usb_interface (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_autopm_get_interface_no_resume (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_autopm_put_interface_async (struct usb_interface*) ; 
 scalar_t__ work_pending (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void kick_hub_wq(struct usb_hub *hub)
{
	struct usb_interface *intf;

	if (hub->disconnected || work_pending(&hub->events))
		return;

	/*
	 * Suppress autosuspend until the event is proceed.
	 *
	 * Be careful and make sure that the symmetric operation is
	 * always called. We are here only when there is no pending
	 * work for this hub. Therefore put the interface either when
	 * the new work is called or when it is canceled.
	 */
	intf = to_usb_interface(hub->intfdev);
	usb_autopm_get_interface_no_resume(intf);
	kref_get(&hub->kref);

	if (queue_work(hub_wq, &hub->events))
		return;

	/* the work has already been scheduled */
	usb_autopm_put_interface_async(intf);
	kref_put(&hub->kref, hub_release);
}