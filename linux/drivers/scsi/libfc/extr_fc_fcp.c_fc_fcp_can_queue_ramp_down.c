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
struct fc_lport {TYPE_1__* host; } ;
struct fc_fcp_internal {scalar_t__ last_can_queue_ramp_down_time; } ;
struct TYPE_2__ {int can_queue; int /*<<< orphan*/  host_lock; } ;

/* Variables and functions */
 scalar_t__ FC_CAN_QUEUE_PERIOD ; 
 struct fc_fcp_internal* fc_get_scsi_internal (struct fc_lport*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 scalar_t__ time_before (scalar_t__,scalar_t__) ; 

__attribute__((used)) static bool fc_fcp_can_queue_ramp_down(struct fc_lport *lport)
{
	struct fc_fcp_internal *si = fc_get_scsi_internal(lport);
	unsigned long flags;
	int can_queue;
	bool changed = false;

	spin_lock_irqsave(lport->host->host_lock, flags);

	if (si->last_can_queue_ramp_down_time &&
	    (time_before(jiffies, si->last_can_queue_ramp_down_time +
			 FC_CAN_QUEUE_PERIOD)))
		goto unlock;

	si->last_can_queue_ramp_down_time = jiffies;

	can_queue = lport->host->can_queue;
	can_queue >>= 1;
	if (!can_queue)
		can_queue = 1;
	lport->host->can_queue = can_queue;
	changed = true;

unlock:
	spin_unlock_irqrestore(lport->host->host_lock, flags);
	return changed;
}