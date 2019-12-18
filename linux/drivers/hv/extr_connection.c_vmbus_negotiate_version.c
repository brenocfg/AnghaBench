#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_6__ {int /*<<< orphan*/  msg_conn_id; scalar_t__ version_supported; } ;
struct TYPE_7__ {TYPE_2__ version_response; } ;
struct vmbus_channel_msginfo {TYPE_3__ response; int /*<<< orphan*/  msglistentry; int /*<<< orphan*/  waitevent; scalar_t__ msg; } ;
struct TYPE_5__ {int /*<<< orphan*/  msgtype; } ;
struct vmbus_channel_initiate_contact {scalar_t__ target_vcpu; void* monitor_page2; void* monitor_page1; void* interrupt_page; int /*<<< orphan*/  msg_sint; scalar_t__ vmbus_version_requested; TYPE_1__ header; } ;
struct TYPE_8__ {unsigned int connect_cpu; int /*<<< orphan*/  msg_conn_id; int /*<<< orphan*/  conn_state; int /*<<< orphan*/  channelmsg_lock; int /*<<< orphan*/  chn_msg_list; int /*<<< orphan*/ * monitor_pages; int /*<<< orphan*/  int_page; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHANNELMSG_INITIATE_CONTACT ; 
 int /*<<< orphan*/  CONNECTED ; 
 int ECONNREFUSED ; 
 scalar_t__ VERSION_WIN10_V5 ; 
 scalar_t__ VERSION_WIN8_1 ; 
 int /*<<< orphan*/  VMBUS_MESSAGE_CONNECTION_ID ; 
 int /*<<< orphan*/  VMBUS_MESSAGE_CONNECTION_ID_4 ; 
 int /*<<< orphan*/  VMBUS_MESSAGE_SINT ; 
 unsigned int get_cpu () ; 
 scalar_t__ hv_cpu_number_to_vp_number (unsigned int) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct vmbus_channel_initiate_contact*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  put_cpu () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  trace_vmbus_negotiate_version (struct vmbus_channel_initiate_contact*,int) ; 
 void* virt_to_phys (int /*<<< orphan*/ ) ; 
 TYPE_4__ vmbus_connection ; 
 int vmbus_post_msg (struct vmbus_channel_initiate_contact*,int,int) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

int vmbus_negotiate_version(struct vmbus_channel_msginfo *msginfo, u32 version)
{
	int ret = 0;
	unsigned int cur_cpu;
	struct vmbus_channel_initiate_contact *msg;
	unsigned long flags;

	init_completion(&msginfo->waitevent);

	msg = (struct vmbus_channel_initiate_contact *)msginfo->msg;

	memset(msg, 0, sizeof(*msg));
	msg->header.msgtype = CHANNELMSG_INITIATE_CONTACT;
	msg->vmbus_version_requested = version;

	/*
	 * VMBus protocol 5.0 (VERSION_WIN10_V5) requires that we must use
	 * VMBUS_MESSAGE_CONNECTION_ID_4 for the Initiate Contact Message,
	 * and for subsequent messages, we must use the Message Connection ID
	 * field in the host-returned Version Response Message. And, with
	 * VERSION_WIN10_V5, we don't use msg->interrupt_page, but we tell
	 * the host explicitly that we still use VMBUS_MESSAGE_SINT(2) for
	 * compatibility.
	 *
	 * On old hosts, we should always use VMBUS_MESSAGE_CONNECTION_ID (1).
	 */
	if (version >= VERSION_WIN10_V5) {
		msg->msg_sint = VMBUS_MESSAGE_SINT;
		vmbus_connection.msg_conn_id = VMBUS_MESSAGE_CONNECTION_ID_4;
	} else {
		msg->interrupt_page = virt_to_phys(vmbus_connection.int_page);
		vmbus_connection.msg_conn_id = VMBUS_MESSAGE_CONNECTION_ID;
	}

	msg->monitor_page1 = virt_to_phys(vmbus_connection.monitor_pages[0]);
	msg->monitor_page2 = virt_to_phys(vmbus_connection.monitor_pages[1]);
	/*
	 * We want all channel messages to be delivered on CPU 0.
	 * This has been the behavior pre-win8. This is not
	 * perf issue and having all channel messages delivered on CPU 0
	 * would be ok.
	 * For post win8 hosts, we support receiving channel messagges on
	 * all the CPUs. This is needed for kexec to work correctly where
	 * the CPU attempting to connect may not be CPU 0.
	 */
	if (version >= VERSION_WIN8_1) {
		cur_cpu = get_cpu();
		msg->target_vcpu = hv_cpu_number_to_vp_number(cur_cpu);
		vmbus_connection.connect_cpu = cur_cpu;
		put_cpu();
	} else {
		msg->target_vcpu = 0;
		vmbus_connection.connect_cpu = 0;
	}

	/*
	 * Add to list before we send the request since we may
	 * receive the response before returning from this routine
	 */
	spin_lock_irqsave(&vmbus_connection.channelmsg_lock, flags);
	list_add_tail(&msginfo->msglistentry,
		      &vmbus_connection.chn_msg_list);

	spin_unlock_irqrestore(&vmbus_connection.channelmsg_lock, flags);

	ret = vmbus_post_msg(msg,
			     sizeof(struct vmbus_channel_initiate_contact),
			     true);

	trace_vmbus_negotiate_version(msg, ret);

	if (ret != 0) {
		spin_lock_irqsave(&vmbus_connection.channelmsg_lock, flags);
		list_del(&msginfo->msglistentry);
		spin_unlock_irqrestore(&vmbus_connection.channelmsg_lock,
					flags);
		return ret;
	}

	/* Wait for the connection response */
	wait_for_completion(&msginfo->waitevent);

	spin_lock_irqsave(&vmbus_connection.channelmsg_lock, flags);
	list_del(&msginfo->msglistentry);
	spin_unlock_irqrestore(&vmbus_connection.channelmsg_lock, flags);

	/* Check if successful */
	if (msginfo->response.version_response.version_supported) {
		vmbus_connection.conn_state = CONNECTED;

		if (version >= VERSION_WIN10_V5)
			vmbus_connection.msg_conn_id =
				msginfo->response.version_response.msg_conn_id;
	} else {
		return -ECONNREFUSED;
	}

	return ret;
}