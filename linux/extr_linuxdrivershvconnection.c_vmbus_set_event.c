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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  child_relid; } ;
struct vmbus_channel {int /*<<< orphan*/  sig_event; int /*<<< orphan*/  sig_events; int /*<<< orphan*/  is_dedicated_interrupt; TYPE_1__ offermsg; } ;

/* Variables and functions */
 int /*<<< orphan*/  HVCALL_SIGNAL_EVENT ; 
 int /*<<< orphan*/  hv_do_fast_hypercall8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmbus_send_interrupt (int /*<<< orphan*/ ) ; 

void vmbus_set_event(struct vmbus_channel *channel)
{
	u32 child_relid = channel->offermsg.child_relid;

	if (!channel->is_dedicated_interrupt)
		vmbus_send_interrupt(child_relid);

	++channel->sig_events;

	hv_do_fast_hypercall8(HVCALL_SIGNAL_EVENT, channel->sig_event);
}