#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
union hv_synic_event_flags {int /*<<< orphan*/  flags; } ;
struct hv_per_cpu_context {int /*<<< orphan*/  msg_dpc; void* synic_message_page; void* synic_event_page; } ;
struct TYPE_3__ {scalar_t__ message_type; } ;
struct hv_message {TYPE_1__ header; } ;
struct TYPE_4__ {int /*<<< orphan*/  cpu_context; } ;

/* Variables and functions */
 scalar_t__ HVMSG_NONE ; 
 scalar_t__ HVMSG_TIMER_EXPIRED ; 
 int /*<<< orphan*/  HYPERVISOR_CALLBACK_VECTOR ; 
 scalar_t__ VERSION_WIN7 ; 
 scalar_t__ VERSION_WS2008 ; 
 int VMBUS_MESSAGE_SINT ; 
 int /*<<< orphan*/  add_interrupt_randomness (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__ hv_context ; 
 int /*<<< orphan*/  hv_stimer0_isr () ; 
 scalar_t__ sync_test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 
 struct hv_per_cpu_context* this_cpu_ptr (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmbus_chan_sched (struct hv_per_cpu_context*) ; 
 scalar_t__ vmbus_proto_version ; 
 int /*<<< orphan*/  vmbus_signal_eom (struct hv_message*,scalar_t__) ; 

__attribute__((used)) static void vmbus_isr(void)
{
	struct hv_per_cpu_context *hv_cpu
		= this_cpu_ptr(hv_context.cpu_context);
	void *page_addr = hv_cpu->synic_event_page;
	struct hv_message *msg;
	union hv_synic_event_flags *event;
	bool handled = false;

	if (unlikely(page_addr == NULL))
		return;

	event = (union hv_synic_event_flags *)page_addr +
					 VMBUS_MESSAGE_SINT;
	/*
	 * Check for events before checking for messages. This is the order
	 * in which events and messages are checked in Windows guests on
	 * Hyper-V, and the Windows team suggested we do the same.
	 */

	if ((vmbus_proto_version == VERSION_WS2008) ||
		(vmbus_proto_version == VERSION_WIN7)) {

		/* Since we are a child, we only need to check bit 0 */
		if (sync_test_and_clear_bit(0, event->flags))
			handled = true;
	} else {
		/*
		 * Our host is win8 or above. The signaling mechanism
		 * has changed and we can directly look at the event page.
		 * If bit n is set then we have an interrup on the channel
		 * whose id is n.
		 */
		handled = true;
	}

	if (handled)
		vmbus_chan_sched(hv_cpu);

	page_addr = hv_cpu->synic_message_page;
	msg = (struct hv_message *)page_addr + VMBUS_MESSAGE_SINT;

	/* Check if there are actual msgs to be processed */
	if (msg->header.message_type != HVMSG_NONE) {
		if (msg->header.message_type == HVMSG_TIMER_EXPIRED) {
			hv_stimer0_isr();
			vmbus_signal_eom(msg, HVMSG_TIMER_EXPIRED);
		} else
			tasklet_schedule(&hv_cpu->msg_dpc);
	}

	add_interrupt_randomness(HYPERVISOR_CALLBACK_VECTOR, 0);
}