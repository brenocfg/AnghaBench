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
typedef  int u8 ;
struct vmbus_channel_offer_channel {scalar_t__ is_dedicated_interrupt; scalar_t__ monitorid; int /*<<< orphan*/  connection_id; int /*<<< orphan*/  child_relid; } ;
struct vmbus_channel_message_header {int dummy; } ;
struct vmbus_channel {int is_dedicated_interrupt; int monitor_grp; int monitor_bit; int /*<<< orphan*/  offermsg; int /*<<< orphan*/  sig_event; } ;
struct TYPE_2__ {int /*<<< orphan*/  offer_in_progress; } ;

/* Variables and functions */
 scalar_t__ VERSION_WS2008 ; 
 int /*<<< orphan*/  VMBUS_EVENT_CONNECTION_ID ; 
 struct vmbus_channel* alloc_channel () ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct vmbus_channel_offer_channel*,int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  trace_vmbus_onoffer (struct vmbus_channel_offer_channel*) ; 
 TYPE_1__ vmbus_connection ; 
 int /*<<< orphan*/  vmbus_process_offer (struct vmbus_channel*) ; 
 scalar_t__ vmbus_proto_version ; 
 int /*<<< orphan*/  vmbus_release_relid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vmbus_onoffer(struct vmbus_channel_message_header *hdr)
{
	struct vmbus_channel_offer_channel *offer;
	struct vmbus_channel *newchannel;

	offer = (struct vmbus_channel_offer_channel *)hdr;

	trace_vmbus_onoffer(offer);

	/* Allocate the channel object and save this offer. */
	newchannel = alloc_channel();
	if (!newchannel) {
		vmbus_release_relid(offer->child_relid);
		atomic_dec(&vmbus_connection.offer_in_progress);
		pr_err("Unable to allocate channel object\n");
		return;
	}

	/*
	 * Setup state for signalling the host.
	 */
	newchannel->sig_event = VMBUS_EVENT_CONNECTION_ID;

	if (vmbus_proto_version != VERSION_WS2008) {
		newchannel->is_dedicated_interrupt =
				(offer->is_dedicated_interrupt != 0);
		newchannel->sig_event = offer->connection_id;
	}

	memcpy(&newchannel->offermsg, offer,
	       sizeof(struct vmbus_channel_offer_channel));
	newchannel->monitor_grp = (u8)offer->monitorid / 32;
	newchannel->monitor_bit = (u8)offer->monitorid % 32;

	vmbus_process_offer(newchannel);
}