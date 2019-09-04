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
struct vmbus_channel_message_header {int /*<<< orphan*/  msgtype; } ;
struct TYPE_2__ {int /*<<< orphan*/  unload_event; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHANNELMSG_UNLOAD ; 
 scalar_t__ VERSION_WIN8_1 ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct vmbus_channel_message_header*,int /*<<< orphan*/ ,int) ; 
 TYPE_1__ vmbus_connection ; 
 int /*<<< orphan*/  vmbus_post_msg (struct vmbus_channel_message_header*,int,int) ; 
 scalar_t__ vmbus_proto_version ; 
 int /*<<< orphan*/  vmbus_wait_for_unload () ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

void vmbus_initiate_unload(bool crash)
{
	struct vmbus_channel_message_header hdr;

	/* Pre-Win2012R2 hosts don't support reconnect */
	if (vmbus_proto_version < VERSION_WIN8_1)
		return;

	init_completion(&vmbus_connection.unload_event);
	memset(&hdr, 0, sizeof(struct vmbus_channel_message_header));
	hdr.msgtype = CHANNELMSG_UNLOAD;
	vmbus_post_msg(&hdr, sizeof(struct vmbus_channel_message_header),
		       !crash);

	/*
	 * vmbus_initiate_unload() is also called on crash and the crash can be
	 * happening in an interrupt context, where scheduling is impossible.
	 */
	if (!crash)
		wait_for_completion(&vmbus_connection.unload_event);
	else
		vmbus_wait_for_unload();
}