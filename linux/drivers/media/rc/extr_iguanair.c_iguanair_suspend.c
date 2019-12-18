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
struct iguanair {int /*<<< orphan*/  lock; int /*<<< orphan*/  urb_out; int /*<<< orphan*/  urb_in; int /*<<< orphan*/  dev; scalar_t__ receiver_on; } ;
typedef  int /*<<< orphan*/  pm_message_t ;

/* Variables and functions */
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int iguanair_receiver (struct iguanair*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct iguanair* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int iguanair_suspend(struct usb_interface *intf, pm_message_t message)
{
	struct iguanair *ir = usb_get_intfdata(intf);
	int rc = 0;

	mutex_lock(&ir->lock);

	if (ir->receiver_on) {
		rc = iguanair_receiver(ir, false);
		if (rc)
			dev_warn(ir->dev, "failed to disable receiver for suspend\n");
	}

	usb_kill_urb(ir->urb_in);
	usb_kill_urb(ir->urb_out);

	mutex_unlock(&ir->lock);

	return rc;
}