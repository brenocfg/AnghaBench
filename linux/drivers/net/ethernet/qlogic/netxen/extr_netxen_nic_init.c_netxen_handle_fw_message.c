#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct status_desc {int /*<<< orphan*/ * status_desc_data; } ;
struct nx_host_sds_ring {int /*<<< orphan*/  adapter; int /*<<< orphan*/  num_desc; struct status_desc* desc_head; } ;
struct TYPE_3__ {int /*<<< orphan*/ * body; void** words; } ;
typedef  TYPE_1__ nx_fw_msg_t ;

/* Variables and functions */
#define  NX_NIC_C2H_OPCODE_GET_LINKEVENT_RESPONSE 128 
 int get_next_index (int,int /*<<< orphan*/ ) ; 
 void* le64_to_cpu (int /*<<< orphan*/ ) ; 
 int netxen_get_nic_msg_opcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netxen_handle_linkevent (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static void
netxen_handle_fw_message(int desc_cnt, int index,
		struct nx_host_sds_ring *sds_ring)
{
	nx_fw_msg_t msg;
	struct status_desc *desc;
	int i = 0, opcode;

	while (desc_cnt > 0 && i < 8) {
		desc = &sds_ring->desc_head[index];
		msg.words[i++] = le64_to_cpu(desc->status_desc_data[0]);
		msg.words[i++] = le64_to_cpu(desc->status_desc_data[1]);

		index = get_next_index(index, sds_ring->num_desc);
		desc_cnt--;
	}

	opcode = netxen_get_nic_msg_opcode(msg.body[0]);
	switch (opcode) {
	case NX_NIC_C2H_OPCODE_GET_LINKEVENT_RESPONSE:
		netxen_handle_linkevent(sds_ring->adapter, &msg);
		break;
	default:
		break;
	}
}