#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mtu3 {int /*<<< orphan*/  g; int /*<<< orphan*/  lock; TYPE_1__* gadget_driver; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* disconnect ) (int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  USB_STATE_NOTATTACHED ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mtu3_state_reset (struct mtu3*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_gadget_set_state (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void mtu3_gadget_disconnect(struct mtu3 *mtu)
{
	dev_dbg(mtu->dev, "gadget DISCONNECT\n");
	if (mtu->gadget_driver && mtu->gadget_driver->disconnect) {
		spin_unlock(&mtu->lock);
		mtu->gadget_driver->disconnect(&mtu->g);
		spin_lock(&mtu->lock);
	}

	mtu3_state_reset(mtu);
	usb_gadget_set_state(&mtu->g, USB_STATE_NOTATTACHED);
}