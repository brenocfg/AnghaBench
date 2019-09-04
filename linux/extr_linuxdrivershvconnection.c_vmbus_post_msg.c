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
struct TYPE_3__ {int /*<<< orphan*/  id; } ;
union hv_connection_id {TYPE_1__ u; scalar_t__ asu32; } ;
typedef  int u32 ;
struct vmbus_channel_message_header {int /*<<< orphan*/  msgtype; } ;
struct TYPE_4__ {int /*<<< orphan*/  msg_conn_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHANNELMSG_INITIATE_CONTACT ; 
 int EAGAIN ; 
 int EINVAL ; 
 int ENOBUFS ; 
#define  HV_STATUS_INSUFFICIENT_BUFFERS 131 
#define  HV_STATUS_INSUFFICIENT_MEMORY 130 
#define  HV_STATUS_INVALID_CONNECTION_ID 129 
#define  HV_STATUS_SUCCESS 128 
 int MAX_UDELAY_MS ; 
 int hv_post_message (union hv_connection_id,int,void*,size_t) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  udelay (int) ; 
 TYPE_2__ vmbus_connection ; 

int vmbus_post_msg(void *buffer, size_t buflen, bool can_sleep)
{
	struct vmbus_channel_message_header *hdr;
	union hv_connection_id conn_id;
	int ret = 0;
	int retries = 0;
	u32 usec = 1;

	conn_id.asu32 = 0;
	conn_id.u.id = vmbus_connection.msg_conn_id;

	/*
	 * hv_post_message() can have transient failures because of
	 * insufficient resources. Retry the operation a couple of
	 * times before giving up.
	 */
	while (retries < 100) {
		ret = hv_post_message(conn_id, 1, buffer, buflen);

		switch (ret) {
		case HV_STATUS_INVALID_CONNECTION_ID:
			/*
			 * See vmbus_negotiate_version(): VMBus protocol 5.0
			 * requires that we must use
			 * VMBUS_MESSAGE_CONNECTION_ID_4 for the Initiate
			 * Contact message, but on old hosts that only
			 * support VMBus protocol 4.0 or lower, here we get
			 * HV_STATUS_INVALID_CONNECTION_ID and we should
			 * return an error immediately without retrying.
			 */
			hdr = buffer;
			if (hdr->msgtype == CHANNELMSG_INITIATE_CONTACT)
				return -EINVAL;
			/*
			 * We could get this if we send messages too
			 * frequently.
			 */
			ret = -EAGAIN;
			break;
		case HV_STATUS_INSUFFICIENT_MEMORY:
		case HV_STATUS_INSUFFICIENT_BUFFERS:
			ret = -ENOBUFS;
			break;
		case HV_STATUS_SUCCESS:
			return ret;
		default:
			pr_err("hv_post_msg() failed; error code:%d\n", ret);
			return -EINVAL;
		}

		retries++;
		if (can_sleep && usec > 1000)
			msleep(usec / 1000);
		else if (usec < MAX_UDELAY_MS * 1000)
			udelay(usec);
		else
			mdelay(usec / 1000);

		if (retries < 22)
			usec *= 2;
	}
	return ret;
}