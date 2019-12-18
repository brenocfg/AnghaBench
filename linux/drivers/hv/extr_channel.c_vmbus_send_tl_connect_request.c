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
struct TYPE_2__ {int /*<<< orphan*/  msgtype; } ;
struct vmbus_channel_tl_connect_request {int /*<<< orphan*/  host_service_id; int /*<<< orphan*/  guest_endpoint_id; TYPE_1__ header; } ;
typedef  int /*<<< orphan*/  guid_t ;
typedef  int /*<<< orphan*/  conn_msg ;

/* Variables and functions */
 int /*<<< orphan*/  CHANNELMSG_TL_CONNECT_REQUEST ; 
 int /*<<< orphan*/  memset (struct vmbus_channel_tl_connect_request*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  trace_vmbus_send_tl_connect_request (struct vmbus_channel_tl_connect_request*,int) ; 
 int vmbus_post_msg (struct vmbus_channel_tl_connect_request*,int,int) ; 

int vmbus_send_tl_connect_request(const guid_t *shv_guest_servie_id,
				  const guid_t *shv_host_servie_id)
{
	struct vmbus_channel_tl_connect_request conn_msg;
	int ret;

	memset(&conn_msg, 0, sizeof(conn_msg));
	conn_msg.header.msgtype = CHANNELMSG_TL_CONNECT_REQUEST;
	conn_msg.guest_endpoint_id = *shv_guest_servie_id;
	conn_msg.host_service_id = *shv_host_servie_id;

	ret = vmbus_post_msg(&conn_msg, sizeof(conn_msg), true);

	trace_vmbus_send_tl_connect_request(&conn_msg, ret);

	return ret;
}