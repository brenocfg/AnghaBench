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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  scalar_t__ u32 ;
struct vmbuspipe_hdr {int dummy; } ;
struct vmbus_channel {int dummy; } ;
struct shutdown_msg_data {int flags; } ;
struct icmsg_hdr {scalar_t__ icmsgtype; int icflags; int /*<<< orphan*/  status; } ;
struct TYPE_2__ {int /*<<< orphan*/ * recv_buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  FW_VER_COUNT ; 
 int /*<<< orphan*/  HV_E_FAIL ; 
 int /*<<< orphan*/  HV_S_OK ; 
 int ICMSGHDRFLAG_RESPONSE ; 
 int ICMSGHDRFLAG_TRANSACTION ; 
 scalar_t__ ICMSGTYPE_NEGOTIATE ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  SD_VER_COUNT ; 
 int /*<<< orphan*/  VM_PKT_DATA_INBAND ; 
 int /*<<< orphan*/  fw_versions ; 
 int /*<<< orphan*/  pr_info (char*,...) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int sd_srv_version ; 
 int /*<<< orphan*/  sd_versions ; 
 int /*<<< orphan*/  shutdown_work ; 
 TYPE_1__ util_shutdown ; 
 scalar_t__ vmbus_prep_negotiate_resp (struct icmsg_hdr*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  vmbus_recvpacket (struct vmbus_channel*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmbus_sendpacket (struct vmbus_channel*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void shutdown_onchannelcallback(void *context)
{
	struct vmbus_channel *channel = context;
	u32 recvlen;
	u64 requestid;
	bool execute_shutdown = false;
	u8  *shut_txf_buf = util_shutdown.recv_buffer;

	struct shutdown_msg_data *shutdown_msg;

	struct icmsg_hdr *icmsghdrp;

	vmbus_recvpacket(channel, shut_txf_buf,
			 PAGE_SIZE, &recvlen, &requestid);

	if (recvlen > 0) {
		icmsghdrp = (struct icmsg_hdr *)&shut_txf_buf[
			sizeof(struct vmbuspipe_hdr)];

		if (icmsghdrp->icmsgtype == ICMSGTYPE_NEGOTIATE) {
			if (vmbus_prep_negotiate_resp(icmsghdrp, shut_txf_buf,
					fw_versions, FW_VER_COUNT,
					sd_versions, SD_VER_COUNT,
					NULL, &sd_srv_version)) {
				pr_info("Shutdown IC version %d.%d\n",
					sd_srv_version >> 16,
					sd_srv_version & 0xFFFF);
			}
		} else {
			shutdown_msg =
				(struct shutdown_msg_data *)&shut_txf_buf[
					sizeof(struct vmbuspipe_hdr) +
					sizeof(struct icmsg_hdr)];

			switch (shutdown_msg->flags) {
			case 0:
			case 1:
				icmsghdrp->status = HV_S_OK;
				execute_shutdown = true;

				pr_info("Shutdown request received -"
					    " graceful shutdown initiated\n");
				break;
			default:
				icmsghdrp->status = HV_E_FAIL;
				execute_shutdown = false;

				pr_info("Shutdown request received -"
					    " Invalid request\n");
				break;
			}
		}

		icmsghdrp->icflags = ICMSGHDRFLAG_TRANSACTION
			| ICMSGHDRFLAG_RESPONSE;

		vmbus_sendpacket(channel, shut_txf_buf,
				       recvlen, requestid,
				       VM_PKT_DATA_INBAND, 0);
	}

	if (execute_shutdown == true)
		schedule_work(&shutdown_work);
}