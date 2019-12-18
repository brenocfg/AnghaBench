#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct usb_interface {int dummy; } ;
struct TYPE_4__ {TYPE_1__* usb; } ;
struct cardstate {int connected; int /*<<< orphan*/  dev; TYPE_2__ hw; } ;
struct TYPE_3__ {int /*<<< orphan*/  read_urb; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_SUSPEND ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  gig_dbg (int /*<<< orphan*/ ,char*) ; 
 struct cardstate* usb_get_intfdata (struct usb_interface*) ; 
 int usb_submit_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gigaset_resume(struct usb_interface *intf)
{
	struct cardstate *cs = usb_get_intfdata(intf);
	int rc;

	/* resubmit interrupt URB */
	cs->connected = 1;
	rc = usb_submit_urb(cs->hw.usb->read_urb, GFP_KERNEL);
	if (rc) {
		dev_err(cs->dev, "Could not submit read URB (error %d)\n", -rc);
		return rc;
	}

	gig_dbg(DEBUG_SUSPEND, "resume complete");
	return 0;
}