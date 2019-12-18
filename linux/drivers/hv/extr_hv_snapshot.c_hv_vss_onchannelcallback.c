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
typedef  scalar_t__ u32 ;
struct vmbuspipe_hdr {int dummy; } ;
struct vmbus_channel {int dummy; } ;
struct icmsg_hdr {scalar_t__ icmsgtype; int icflags; } ;
struct hv_vss_msg {int dummy; } ;
struct TYPE_2__ {scalar_t__ state; struct hv_vss_msg* msg; int /*<<< orphan*/  recv_req_id; scalar_t__ recv_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  FW_VER_COUNT ; 
 scalar_t__ HVUTIL_READY ; 
 int ICMSGHDRFLAG_RESPONSE ; 
 int ICMSGHDRFLAG_TRANSACTION ; 
 scalar_t__ ICMSGTYPE_NEGOTIATE ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  VM_PKT_DATA_INBAND ; 
 int /*<<< orphan*/  VSS_VER_COUNT ; 
 int /*<<< orphan*/  fw_versions ; 
 int /*<<< orphan*/  pr_info (char*,int,int) ; 
 int /*<<< orphan*/ * recv_buffer ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 scalar_t__ vmbus_prep_negotiate_resp (struct icmsg_hdr*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  vmbus_recvpacket (struct vmbus_channel*,int /*<<< orphan*/ *,int,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmbus_sendpacket (struct vmbus_channel*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vss_handle_request_work ; 
 TYPE_1__ vss_transaction ; 
 int /*<<< orphan*/  vss_versions ; 

void hv_vss_onchannelcallback(void *context)
{
	struct vmbus_channel *channel = context;
	u32 recvlen;
	u64 requestid;
	struct hv_vss_msg *vss_msg;
	int vss_srv_version;

	struct icmsg_hdr *icmsghdrp;

	if (vss_transaction.state > HVUTIL_READY)
		return;

	vmbus_recvpacket(channel, recv_buffer, PAGE_SIZE * 2, &recvlen,
			 &requestid);

	if (recvlen > 0) {
		icmsghdrp = (struct icmsg_hdr *)&recv_buffer[
			sizeof(struct vmbuspipe_hdr)];

		if (icmsghdrp->icmsgtype == ICMSGTYPE_NEGOTIATE) {
			if (vmbus_prep_negotiate_resp(icmsghdrp,
				 recv_buffer, fw_versions, FW_VER_COUNT,
				 vss_versions, VSS_VER_COUNT,
				 NULL, &vss_srv_version)) {

				pr_info("VSS IC version %d.%d\n",
					vss_srv_version >> 16,
					vss_srv_version & 0xFFFF);
			}
		} else {
			vss_msg = (struct hv_vss_msg *)&recv_buffer[
				sizeof(struct vmbuspipe_hdr) +
				sizeof(struct icmsg_hdr)];

			/*
			 * Stash away this global state for completing the
			 * transaction; note transactions are serialized.
			 */

			vss_transaction.recv_len = recvlen;
			vss_transaction.recv_req_id = requestid;
			vss_transaction.msg = (struct hv_vss_msg *)vss_msg;

			schedule_work(&vss_handle_request_work);
			return;
		}

		icmsghdrp->icflags = ICMSGHDRFLAG_TRANSACTION
			| ICMSGHDRFLAG_RESPONSE;

		vmbus_sendpacket(channel, recv_buffer,
				       recvlen, requestid,
				       VM_PKT_DATA_INBAND, 0);
	}

}