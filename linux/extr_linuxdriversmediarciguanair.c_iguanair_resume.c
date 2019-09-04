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
struct usb_interface {int /*<<< orphan*/  dev; } ;
struct iguanair {int /*<<< orphan*/  lock; int /*<<< orphan*/  dev; scalar_t__ receiver_on; int /*<<< orphan*/  urb_in; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,...) ; 
 int iguanair_receiver (struct iguanair*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct iguanair* usb_get_intfdata (struct usb_interface*) ; 
 int usb_submit_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int iguanair_resume(struct usb_interface *intf)
{
	struct iguanair *ir = usb_get_intfdata(intf);
	int rc = 0;

	mutex_lock(&ir->lock);

	rc = usb_submit_urb(ir->urb_in, GFP_KERNEL);
	if (rc)
		dev_warn(&intf->dev, "failed to submit urb: %d\n", rc);

	if (ir->receiver_on) {
		rc = iguanair_receiver(ir, true);
		if (rc)
			dev_warn(ir->dev, "failed to enable receiver after resume\n");
	}

	mutex_unlock(&ir->lock);

	return rc;
}