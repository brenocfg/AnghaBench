#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  scalar_t__ u32 ;
struct vmbuspipe_hdr {int dummy; } ;
struct vmbus_channel {int dummy; } ;
struct ictimesync_ref_data {int /*<<< orphan*/  flags; int /*<<< orphan*/  vmreferencetime; int /*<<< orphan*/  parenttime; } ;
struct ictimesync_data {int /*<<< orphan*/  flags; int /*<<< orphan*/  parenttime; } ;
struct icmsg_hdr {scalar_t__ icmsgtype; int icflags; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* read ) (TYPE_2__*) ;} ;
struct TYPE_4__ {int /*<<< orphan*/ * recv_buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  FW_VER_COUNT ; 
 int ICMSGHDRFLAG_RESPONSE ; 
 int ICMSGHDRFLAG_TRANSACTION ; 
 scalar_t__ ICMSGTYPE_NEGOTIATE ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int TS_VERSION_3 ; 
 int /*<<< orphan*/  TS_VER_COUNT ; 
 int /*<<< orphan*/  VM_PKT_DATA_INBAND ; 
 int /*<<< orphan*/  adj_guesttime (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fw_versions ; 
 TYPE_2__* hyperv_cs ; 
 int /*<<< orphan*/  pr_info (char*,int,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 
 int ts_srv_version ; 
 int /*<<< orphan*/  ts_versions ; 
 TYPE_1__ util_timesynch ; 
 scalar_t__ vmbus_prep_negotiate_resp (struct icmsg_hdr*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  vmbus_recvpacket (struct vmbus_channel*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmbus_sendpacket (struct vmbus_channel*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void timesync_onchannelcallback(void *context)
{
	struct vmbus_channel *channel = context;
	u32 recvlen;
	u64 requestid;
	struct icmsg_hdr *icmsghdrp;
	struct ictimesync_data *timedatap;
	struct ictimesync_ref_data *refdata;
	u8 *time_txf_buf = util_timesynch.recv_buffer;

	vmbus_recvpacket(channel, time_txf_buf,
			 PAGE_SIZE, &recvlen, &requestid);

	if (recvlen > 0) {
		icmsghdrp = (struct icmsg_hdr *)&time_txf_buf[
				sizeof(struct vmbuspipe_hdr)];

		if (icmsghdrp->icmsgtype == ICMSGTYPE_NEGOTIATE) {
			if (vmbus_prep_negotiate_resp(icmsghdrp, time_txf_buf,
						fw_versions, FW_VER_COUNT,
						ts_versions, TS_VER_COUNT,
						NULL, &ts_srv_version)) {
				pr_info("TimeSync IC version %d.%d\n",
					ts_srv_version >> 16,
					ts_srv_version & 0xFFFF);
			}
		} else {
			if (ts_srv_version > TS_VERSION_3) {
				refdata = (struct ictimesync_ref_data *)
					&time_txf_buf[
					sizeof(struct vmbuspipe_hdr) +
					sizeof(struct icmsg_hdr)];

				adj_guesttime(refdata->parenttime,
						refdata->vmreferencetime,
						refdata->flags);
			} else {
				timedatap = (struct ictimesync_data *)
					&time_txf_buf[
					sizeof(struct vmbuspipe_hdr) +
					sizeof(struct icmsg_hdr)];
				adj_guesttime(timedatap->parenttime,
					      hyperv_cs->read(hyperv_cs),
					      timedatap->flags);
			}
		}

		icmsghdrp->icflags = ICMSGHDRFLAG_TRANSACTION
			| ICMSGHDRFLAG_RESPONSE;

		vmbus_sendpacket(channel, time_txf_buf,
				recvlen, requestid,
				VM_PKT_DATA_INBAND, 0);
	}
}