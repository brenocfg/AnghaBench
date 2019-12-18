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
struct adu_device {int /*<<< orphan*/  buflock; int /*<<< orphan*/  interrupt_out_urb; int /*<<< orphan*/  out_urb_finished; int /*<<< orphan*/  write_wait; int /*<<< orphan*/  interrupt_in_urb; int /*<<< orphan*/  read_urb_finished; scalar_t__ disconnected; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMMAND_TIMEOUT ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_event_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void adu_abort_transfers(struct adu_device *dev)
{
	unsigned long flags;

	if (dev->disconnected)
		return;

	/* shutdown transfer */

	/* XXX Anchor these instead */
	spin_lock_irqsave(&dev->buflock, flags);
	if (!dev->read_urb_finished) {
		spin_unlock_irqrestore(&dev->buflock, flags);
		usb_kill_urb(dev->interrupt_in_urb);
	} else
		spin_unlock_irqrestore(&dev->buflock, flags);

	spin_lock_irqsave(&dev->buflock, flags);
	if (!dev->out_urb_finished) {
		spin_unlock_irqrestore(&dev->buflock, flags);
		wait_event_timeout(dev->write_wait, dev->out_urb_finished,
			COMMAND_TIMEOUT);
		usb_kill_urb(dev->interrupt_out_urb);
	} else
		spin_unlock_irqrestore(&dev->buflock, flags);
}