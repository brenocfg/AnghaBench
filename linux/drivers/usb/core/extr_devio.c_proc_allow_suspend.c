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
struct usb_dev_state {int suspend_allowed; int /*<<< orphan*/  dev; int /*<<< orphan*/  not_yet_resumed; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  connected (struct usb_dev_state*) ; 
 int /*<<< orphan*/  usb_autosuspend_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int proc_allow_suspend(struct usb_dev_state *ps)
{
	if (!connected(ps))
		return -ENODEV;

	WRITE_ONCE(ps->not_yet_resumed, 1);
	if (!ps->suspend_allowed) {
		usb_autosuspend_device(ps->dev);
		ps->suspend_allowed = true;
	}
	return 0;
}