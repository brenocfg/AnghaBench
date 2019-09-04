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
struct mei_me_hw {int /*<<< orphan*/  pg_state; } ;
struct mei_device {scalar_t__ pg_event; int /*<<< orphan*/  wait_pg; } ;

/* Variables and functions */
 scalar_t__ MEI_PG_EVENT_INTR_RECEIVED ; 
 scalar_t__ MEI_PG_EVENT_INTR_WAIT ; 
 int /*<<< orphan*/  MEI_PG_OFF ; 
 struct mei_me_hw* to_me_hw (struct mei_device*) ; 
 scalar_t__ waitqueue_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mei_me_pg_legacy_intr(struct mei_device *dev)
{
	struct mei_me_hw *hw = to_me_hw(dev);

	if (dev->pg_event != MEI_PG_EVENT_INTR_WAIT)
		return;

	dev->pg_event = MEI_PG_EVENT_INTR_RECEIVED;
	hw->pg_state = MEI_PG_OFF;
	if (waitqueue_active(&dev->wait_pg))
		wake_up(&dev->wait_pg);
}