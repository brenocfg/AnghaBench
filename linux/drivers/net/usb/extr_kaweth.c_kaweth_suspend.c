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
struct kaweth_device {int /*<<< orphan*/  device_lock; int /*<<< orphan*/  status; } ;
typedef  int /*<<< orphan*/  pm_message_t ;

/* Variables and functions */
 int /*<<< orphan*/  KAWETH_STATUS_SUSPENDING ; 
 int /*<<< orphan*/  kaweth_kill_urbs (struct kaweth_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct kaweth_device* usb_get_intfdata (struct usb_interface*) ; 

__attribute__((used)) static int kaweth_suspend(struct usb_interface *intf, pm_message_t message)
{
	struct kaweth_device *kaweth = usb_get_intfdata(intf);
	unsigned long flags;

	spin_lock_irqsave(&kaweth->device_lock, flags);
	kaweth->status |= KAWETH_STATUS_SUSPENDING;
	spin_unlock_irqrestore(&kaweth->device_lock, flags);

	kaweth_kill_urbs(kaweth);
	return 0;
}