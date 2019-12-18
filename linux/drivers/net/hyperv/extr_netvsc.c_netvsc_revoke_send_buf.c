#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  id; } ;
struct TYPE_8__ {TYPE_2__ revoke_send_buf; } ;
struct TYPE_9__ {TYPE_3__ v1_msg; } ;
struct TYPE_6__ {int /*<<< orphan*/  msg_type; } ;
struct nvsp_message {TYPE_4__ msg; TYPE_1__ hdr; } ;
struct netvsc_device {scalar_t__ send_section_cnt; struct nvsp_message revoke_packet; } ;
struct net_device {int dummy; } ;
struct hv_device {TYPE_5__* channel; } ;
struct TYPE_10__ {scalar_t__ rescind; } ;

/* Variables and functions */
 int /*<<< orphan*/  NETVSC_SEND_BUFFER_ID ; 
 int /*<<< orphan*/  NVSP_MSG1_TYPE_REVOKE_SEND_BUF ; 
 int /*<<< orphan*/  VM_PKT_DATA_INBAND ; 
 int /*<<< orphan*/  memset (struct nvsp_message*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 int /*<<< orphan*/  trace_nvsp_send (struct net_device*,struct nvsp_message*) ; 
 int vmbus_sendpacket (TYPE_5__*,struct nvsp_message*,int,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void netvsc_revoke_send_buf(struct hv_device *device,
				   struct netvsc_device *net_device,
				   struct net_device *ndev)
{
	struct nvsp_message *revoke_packet;
	int ret;

	/* Deal with the send buffer we may have setup.
	 * If we got a  send section size, it means we received a
	 * NVSP_MSG1_TYPE_SEND_SEND_BUF_COMPLETE msg (ie sent
	 * NVSP_MSG1_TYPE_SEND_SEND_BUF msg) therefore, we need
	 * to send a revoke msg here
	 */
	if (net_device->send_section_cnt) {
		/* Send the revoke receive buffer */
		revoke_packet = &net_device->revoke_packet;
		memset(revoke_packet, 0, sizeof(struct nvsp_message));

		revoke_packet->hdr.msg_type =
			NVSP_MSG1_TYPE_REVOKE_SEND_BUF;
		revoke_packet->msg.v1_msg.revoke_send_buf.id =
			NETVSC_SEND_BUFFER_ID;

		trace_nvsp_send(ndev, revoke_packet);

		ret = vmbus_sendpacket(device->channel,
				       revoke_packet,
				       sizeof(struct nvsp_message),
				       (unsigned long)revoke_packet,
				       VM_PKT_DATA_INBAND, 0);

		/* If the failure is because the channel is rescinded;
		 * ignore the failure since we cannot send on a rescinded
		 * channel. This would allow us to properly cleanup
		 * even when the channel is rescinded.
		 */
		if (device->channel->rescind)
			ret = 0;

		/* If we failed here, we might as well return and
		 * have a leak rather than continue and a bugchk
		 */
		if (ret != 0) {
			netdev_err(ndev, "unable to send "
				   "revoke send buffer to netvsp\n");
			return;
		}
		net_device->send_section_cnt = 0;
	}
}