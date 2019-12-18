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
typedef  scalar_t__ u32 ;
struct uhid_event {scalar_t__ type; } ;
struct uhid_device {scalar_t__ report_type; scalar_t__ report_id; int report_running; int /*<<< orphan*/  qlock; int /*<<< orphan*/  report_wait; int /*<<< orphan*/  report_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct uhid_event const*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void uhid_report_wake_up(struct uhid_device *uhid, u32 id,
				const struct uhid_event *ev)
{
	unsigned long flags;

	spin_lock_irqsave(&uhid->qlock, flags);

	/* id for old report; drop it silently */
	if (uhid->report_type != ev->type || uhid->report_id != id)
		goto unlock;
	if (!uhid->report_running)
		goto unlock;

	memcpy(&uhid->report_buf, ev, sizeof(*ev));
	uhid->report_running = false;
	wake_up_interruptible(&uhid->report_wait);

unlock:
	spin_unlock_irqrestore(&uhid->qlock, flags);
}