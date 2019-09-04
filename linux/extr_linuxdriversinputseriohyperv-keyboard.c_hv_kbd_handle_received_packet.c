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
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct vmpacket_descriptor {int type; int offset8; } ;
struct synth_kbd_msg_hdr {int dummy; } ;
struct synth_kbd_msg {int dummy; } ;
struct hv_device {int /*<<< orphan*/  device; } ;

/* Variables and functions */
#define  VM_PKT_COMP 129 
#define  VM_PKT_DATA_INBAND 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hv_kbd_on_receive (struct hv_device*,struct synth_kbd_msg*,int) ; 

__attribute__((used)) static void hv_kbd_handle_received_packet(struct hv_device *hv_dev,
					  struct vmpacket_descriptor *desc,
					  u32 bytes_recvd,
					  u64 req_id)
{
	struct synth_kbd_msg *msg;
	u32 msg_sz;

	switch (desc->type) {
	case VM_PKT_COMP:
		break;

	case VM_PKT_DATA_INBAND:
		/*
		 * We have a packet that has "inband" data. The API used
		 * for retrieving the packet guarantees that the complete
		 * packet is read. So, minimally, we should be able to
		 * parse the payload header safely (assuming that the host
		 * can be trusted.  Trusting the host seems to be a
		 * reasonable assumption because in a virtualized
		 * environment there is not whole lot you can do if you
		 * don't trust the host.
		 *
		 * Nonetheless, let us validate if the host can be trusted
		 * (in a trivial way).  The interesting aspect of this
		 * validation is how do you recover if we discover that the
		 * host is not to be trusted? Simply dropping the packet, I
		 * don't think is an appropriate recovery.  In the interest
		 * of failing fast, it may be better to crash the guest.
		 * For now, I will just drop the packet!
		 */

		msg_sz = bytes_recvd - (desc->offset8 << 3);
		if (msg_sz <= sizeof(struct synth_kbd_msg_hdr)) {
			/*
			 * Drop the packet and hope
			 * the problem magically goes away.
			 */
			dev_err(&hv_dev->device,
				"Illegal packet (type: %d, tid: %llx, size: %d)\n",
				desc->type, req_id, msg_sz);
			break;
		}

		msg = (void *)desc + (desc->offset8 << 3);
		hv_kbd_on_receive(hv_dev, msg, msg_sz);
		break;

	default:
		dev_err(&hv_dev->device,
			"unhandled packet type %d, tid %llx len %d\n",
			desc->type, req_id, bytes_recvd);
		break;
	}
}