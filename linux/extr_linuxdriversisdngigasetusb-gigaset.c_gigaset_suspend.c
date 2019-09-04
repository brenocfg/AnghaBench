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
struct cardstate {TYPE_2__ hw; int /*<<< orphan*/  write_tasklet; scalar_t__ connected; } ;
typedef  int /*<<< orphan*/  pm_message_t ;
struct TYPE_3__ {int /*<<< orphan*/  bulk_out_urb; int /*<<< orphan*/  read_urb; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_SUSPEND ; 
 int /*<<< orphan*/  gig_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 
 struct cardstate* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gigaset_suspend(struct usb_interface *intf, pm_message_t message)
{
	struct cardstate *cs = usb_get_intfdata(intf);

	/* stop activity */
	cs->connected = 0;	/* prevent rescheduling */
	usb_kill_urb(cs->hw.usb->read_urb);
	tasklet_kill(&cs->write_tasklet);
	usb_kill_urb(cs->hw.usb->bulk_out_urb);

	gig_dbg(DEBUG_SUSPEND, "suspend complete");
	return 0;
}