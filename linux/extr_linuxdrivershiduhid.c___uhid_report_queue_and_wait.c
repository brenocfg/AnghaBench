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
struct uhid_event {scalar_t__ type; } ;
struct uhid_device {int report_running; int /*<<< orphan*/  running; int /*<<< orphan*/  report_wait; int /*<<< orphan*/  qlock; scalar_t__ report_type; scalar_t__ report_id; } ;
typedef  scalar_t__ __u32 ;

/* Variables and functions */
 int EIO ; 
 int ERESTARTSYS ; 
 int HZ ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  uhid_queue (struct uhid_device*,struct uhid_event*) ; 
 int wait_event_interruptible_timeout (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int __uhid_report_queue_and_wait(struct uhid_device *uhid,
					struct uhid_event *ev,
					__u32 *report_id)
{
	unsigned long flags;
	int ret;

	spin_lock_irqsave(&uhid->qlock, flags);
	*report_id = ++uhid->report_id;
	uhid->report_type = ev->type + 1;
	uhid->report_running = true;
	uhid_queue(uhid, ev);
	spin_unlock_irqrestore(&uhid->qlock, flags);

	ret = wait_event_interruptible_timeout(uhid->report_wait,
				!uhid->report_running || !uhid->running,
				5 * HZ);
	if (!ret || !uhid->running || uhid->report_running)
		ret = -EIO;
	else if (ret < 0)
		ret = -ERESTARTSYS;
	else
		ret = 0;

	uhid->report_running = false;

	return ret;
}