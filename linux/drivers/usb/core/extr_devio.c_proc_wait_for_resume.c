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
struct usb_dev_state {int /*<<< orphan*/  dev; int /*<<< orphan*/  not_yet_resumed; int /*<<< orphan*/  wait_for_resume; } ;

/* Variables and functions */
 int EINTR ; 
 scalar_t__ READ_ONCE (int /*<<< orphan*/ ) ; 
 int proc_forbid_suspend (struct usb_dev_state*) ; 
 int /*<<< orphan*/  usb_lock_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_unlock_device (int /*<<< orphan*/ ) ; 
 int wait_event_interruptible (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int proc_wait_for_resume(struct usb_dev_state *ps)
{
	int ret;

	usb_unlock_device(ps->dev);
	ret = wait_event_interruptible(ps->wait_for_resume,
			READ_ONCE(ps->not_yet_resumed) == 0);
	usb_lock_device(ps->dev);

	if (ret != 0)
		return -EINTR;
	return proc_forbid_suspend(ps);
}