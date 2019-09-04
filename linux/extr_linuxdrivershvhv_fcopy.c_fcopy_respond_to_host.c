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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct vmbuspipe_hdr {int dummy; } ;
struct vmbus_channel {int /*<<< orphan*/ * onchannel_callback; } ;
struct icmsg_hdr {int status; int icflags; } ;
struct TYPE_2__ {int /*<<< orphan*/  recv_req_id; struct vmbus_channel* recv_channel; int /*<<< orphan*/  recv_len; } ;

/* Variables and functions */
 int ICMSGHDRFLAG_RESPONSE ; 
 int ICMSGHDRFLAG_TRANSACTION ; 
 int /*<<< orphan*/  VM_PKT_DATA_INBAND ; 
 TYPE_1__ fcopy_transaction ; 
 int /*<<< orphan*/ * recv_buffer ; 
 int /*<<< orphan*/  vmbus_sendpacket (struct vmbus_channel*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
fcopy_respond_to_host(int error)
{
	struct icmsg_hdr *icmsghdr;
	u32 buf_len;
	struct vmbus_channel *channel;
	u64 req_id;

	/*
	 * Copy the global state for completing the transaction. Note that
	 * only one transaction can be active at a time. This is guaranteed
	 * by the file copy protocol implemented by the host. Furthermore,
	 * the "transaction active" state we maintain ensures that there can
	 * only be one active transaction at a time.
	 */

	buf_len = fcopy_transaction.recv_len;
	channel = fcopy_transaction.recv_channel;
	req_id = fcopy_transaction.recv_req_id;

	icmsghdr = (struct icmsg_hdr *)
			&recv_buffer[sizeof(struct vmbuspipe_hdr)];

	if (channel->onchannel_callback == NULL)
		/*
		 * We have raced with util driver being unloaded;
		 * silently return.
		 */
		return;

	icmsghdr->status = error;
	icmsghdr->icflags = ICMSGHDRFLAG_TRANSACTION | ICMSGHDRFLAG_RESPONSE;
	vmbus_sendpacket(channel, recv_buffer, buf_len, req_id,
				VM_PKT_DATA_INBAND, 0);
}