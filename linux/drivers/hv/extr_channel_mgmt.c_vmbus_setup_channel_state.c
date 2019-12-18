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
typedef  int u8 ;
struct vmbus_channel_offer_channel {scalar_t__ is_dedicated_interrupt; scalar_t__ monitorid; int /*<<< orphan*/  connection_id; } ;
struct vmbus_channel {int is_dedicated_interrupt; int monitor_grp; int monitor_bit; int /*<<< orphan*/  offermsg; int /*<<< orphan*/  sig_event; } ;

/* Variables and functions */
 scalar_t__ VERSION_WS2008 ; 
 int /*<<< orphan*/  VMBUS_EVENT_CONNECTION_ID ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct vmbus_channel_offer_channel*,int) ; 
 scalar_t__ vmbus_proto_version ; 

__attribute__((used)) static void vmbus_setup_channel_state(struct vmbus_channel *channel,
				      struct vmbus_channel_offer_channel *offer)
{
	/*
	 * Setup state for signalling the host.
	 */
	channel->sig_event = VMBUS_EVENT_CONNECTION_ID;

	if (vmbus_proto_version != VERSION_WS2008) {
		channel->is_dedicated_interrupt =
				(offer->is_dedicated_interrupt != 0);
		channel->sig_event = offer->connection_id;
	}

	memcpy(&channel->offermsg, offer,
	       sizeof(struct vmbus_channel_offer_channel));
	channel->monitor_grp = (u8)offer->monitorid / 32;
	channel->monitor_bit = (u8)offer->monitorid % 32;
}