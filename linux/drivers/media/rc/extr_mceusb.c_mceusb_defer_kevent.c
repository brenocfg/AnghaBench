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
struct mceusb_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  kevent; int /*<<< orphan*/  kevent_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVENT_RST_PEND ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mceusb_defer_kevent(struct mceusb_dev *ir, int kevent)
{
	set_bit(kevent, &ir->kevent_flags);

	if (test_bit(EVENT_RST_PEND, &ir->kevent_flags)) {
		dev_dbg(ir->dev, "kevent %d dropped pending USB Reset Device",
			kevent);
		return;
	}

	if (!schedule_work(&ir->kevent))
		dev_dbg(ir->dev, "kevent %d already scheduled", kevent);
	else
		dev_dbg(ir->dev, "kevent %d scheduled", kevent);
}