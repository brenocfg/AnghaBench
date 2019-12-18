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
struct vmbus_channel_offer_channel {scalar_t__ child_relid; } ;
struct vmbus_channel_message_header {int dummy; } ;
struct vmbus_channel {struct vmbus_channel_offer_channel offermsg; } ;
struct TYPE_2__ {int /*<<< orphan*/  offer_in_progress; } ;

/* Variables and functions */
 int /*<<< orphan*/  DUMP_PREFIX_OFFSET ; 
 scalar_t__ INVALID_RELID ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct vmbus_channel* alloc_channel () ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  check_ready_for_resume_event () ; 
 struct vmbus_channel* find_primary_channel_by_offer (struct vmbus_channel_offer_channel*) ; 
 scalar_t__ memcmp (struct vmbus_channel_offer_channel*,struct vmbus_channel_offer_channel*,size_t) ; 
 int /*<<< orphan*/  pr_debug (char*,scalar_t__) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  print_hex_dump_debug (char*,int /*<<< orphan*/ ,int,int,struct vmbus_channel_offer_channel*,size_t,int) ; 
 int /*<<< orphan*/  trace_vmbus_onoffer (struct vmbus_channel_offer_channel*) ; 
 TYPE_1__ vmbus_connection ; 
 int /*<<< orphan*/  vmbus_process_offer (struct vmbus_channel*) ; 
 int /*<<< orphan*/  vmbus_release_relid (scalar_t__) ; 
 int /*<<< orphan*/  vmbus_setup_channel_state (struct vmbus_channel*,struct vmbus_channel_offer_channel*) ; 

__attribute__((used)) static void vmbus_onoffer(struct vmbus_channel_message_header *hdr)
{
	struct vmbus_channel_offer_channel *offer;
	struct vmbus_channel *oldchannel, *newchannel;
	size_t offer_sz;

	offer = (struct vmbus_channel_offer_channel *)hdr;

	trace_vmbus_onoffer(offer);

	oldchannel = find_primary_channel_by_offer(offer);

	if (oldchannel != NULL) {
		atomic_dec(&vmbus_connection.offer_in_progress);

		/*
		 * We're resuming from hibernation: all the sub-channel and
		 * hv_sock channels we had before the hibernation should have
		 * been cleaned up, and now we must be seeing a re-offered
		 * primary channel that we had before the hibernation.
		 */

		WARN_ON(oldchannel->offermsg.child_relid != INVALID_RELID);
		/* Fix up the relid. */
		oldchannel->offermsg.child_relid = offer->child_relid;

		offer_sz = sizeof(*offer);
		if (memcmp(offer, &oldchannel->offermsg, offer_sz) == 0) {
			check_ready_for_resume_event();
			return;
		}

		/*
		 * This is not an error, since the host can also change the
		 * other field(s) of the offer, e.g. on WS RS5 (Build 17763),
		 * the offer->connection_id of the Mellanox VF vmbus device
		 * can change when the host reoffers the device upon resume.
		 */
		pr_debug("vmbus offer changed: relid=%d\n",
			 offer->child_relid);

		print_hex_dump_debug("Old vmbus offer: ", DUMP_PREFIX_OFFSET,
				     16, 4, &oldchannel->offermsg, offer_sz,
				     false);
		print_hex_dump_debug("New vmbus offer: ", DUMP_PREFIX_OFFSET,
				     16, 4, offer, offer_sz, false);

		/* Fix up the old channel. */
		vmbus_setup_channel_state(oldchannel, offer);

		check_ready_for_resume_event();

		return;
	}

	/* Allocate the channel object and save this offer. */
	newchannel = alloc_channel();
	if (!newchannel) {
		vmbus_release_relid(offer->child_relid);
		atomic_dec(&vmbus_connection.offer_in_progress);
		pr_err("Unable to allocate channel object\n");
		return;
	}

	vmbus_setup_channel_state(newchannel, offer);

	vmbus_process_offer(newchannel);
}