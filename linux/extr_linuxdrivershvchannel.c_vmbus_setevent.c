#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  child_relid; scalar_t__ monitor_allocated; } ;
struct vmbus_channel {size_t monitor_grp; int /*<<< orphan*/  monitor_bit; TYPE_1__ offermsg; int /*<<< orphan*/  low_latency; } ;
struct hv_monitor_page {TYPE_2__* trigger_group; } ;
struct TYPE_6__ {struct hv_monitor_page** monitor_pages; } ;
struct TYPE_5__ {int /*<<< orphan*/  pending; } ;

/* Variables and functions */
 int /*<<< orphan*/  sync_set_bit (int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  trace_vmbus_setevent (struct vmbus_channel*) ; 
 TYPE_3__ vmbus_connection ; 
 int /*<<< orphan*/  vmbus_send_interrupt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmbus_set_event (struct vmbus_channel*) ; 

void vmbus_setevent(struct vmbus_channel *channel)
{
	struct hv_monitor_page *monitorpage;

	trace_vmbus_setevent(channel);

	/*
	 * For channels marked as in "low latency" mode
	 * bypass the monitor page mechanism.
	 */
	if (channel->offermsg.monitor_allocated && !channel->low_latency) {
		vmbus_send_interrupt(channel->offermsg.child_relid);

		/* Get the child to parent monitor page */
		monitorpage = vmbus_connection.monitor_pages[1];

		sync_set_bit(channel->monitor_bit,
			(unsigned long *)&monitorpage->trigger_group
					[channel->monitor_grp].pending);

	} else {
		vmbus_set_event(channel);
	}
}